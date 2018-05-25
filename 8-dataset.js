'use strict';

let flagForAutoCommit = false;
let isAutoCommit = false;
let timeForAutoCommit = 0;

let flagForAutoRollback = false;
let isAutoRollback = false;
let timeForAutoRollback = 0;

let change = false;

function Transaction() {}

Transaction.start = (data) => {
  console.log('\nstart transaction');
  const events = {
    commit: [], rollback: [], timeout: [], change: []
  };
  let delta = {};

  const emit = (name) => {
    const event = events[name];
    for (const listener of event) listener(data);
  };

  function auto() {
    if (change) {
      if (isAutoCommit) {
        flagForAutoCommit = true;
        methods.autoCommit(timeForAutoCommit);
      }
      if (isAutoRollback) {
        flagForAutoRollback = true;
        methods.autoRollback(timeForAutoRollback);
      }
      change = false;
    }
  }

  const methods = {
    commit: () => {
      Object.assign(data, delta);
      delta = {};
      console.log('Commit');
      emit('commit');
    },
    rollback: () => {
      delta = {};
      console.log('Rollback');
      emit('rollback');
    },
    clone: () => {
      const cloned = Transaction.start(data);
      Object.assign(cloned.delta, delta);
      return cloned;
    },
    on: (name, callback) => {
      const event = events[name];
      if (event) event.push(callback);
    },
    timeout: (msec) => {
      setTimeout(() => {
        delta = {};
        console.log('Rollback');
      }, msec);
    },
    autoCommit: (msec) => {
      isAutoCommit = true;
      timeForAutoCommit = msec;
      if (flagForAutoCommit) {
        setTimeout(() => {
          Object.assign(data, delta);
          delta = {};
          console.log('AutoCommit');
        }, msec);
        flagForAutoCommit = false;
      }
    },
    autoRollback: (msec) => {
      isAutoRollback = true;
      timeForAutoRollback = msec;
      if (flagForAutoRollback) {
        setTimeout(() => {
          delta = {};
          console.log('AutoRollback');
        }, msec);
        flagForAutoRollback = false;
      }
    },
    clearTimeout: () => {
      isAutoCommit = false;
      isAutoRollback = false;
      console.log('Timeouts are turned off');
    }
  };

  return new Proxy(data, {
    get(target, key) {
      if (key === 'delta') return delta;
      if (methods.hasOwnProperty(key)) return methods[key];
      if (delta.hasOwnProperty(key)) return delta[key];
      return target[key];
    },
    getOwnPropertyDescriptor: (target, key) => (
      Object.getOwnPropertyDescriptor(
        delta.hasOwnProperty(key) ? delta : target, key
      )
    ),
    ownKeys() {
      const changes = Object.keys(delta);
      const keys = Object.keys(data).concat(changes);
      return keys.filter((x, i, a) => a.indexOf(x) === i);
    },
    set(target, key, val) {
      change = true;
      console.log('set', key, val);
      if (target[key] === val) delete delta[key];
      else delta[key] = val;
      auto();
      return true;
    }
  });
};

// Usage

const data = { name: 'Marcus', born: 121, city: 'Rome' };

const transaction = Transaction.start(data);

transaction.autoRollback(2000);

setTimeout(() => {transaction.born = 110;}, 1000);
setTimeout(() => {transaction.city = 'Kiev';}, 5000);

setTimeout(() => {transaction.clearTimeout();}, 8000);

setTimeout(() => {transaction.born = 114;}, 11000);
