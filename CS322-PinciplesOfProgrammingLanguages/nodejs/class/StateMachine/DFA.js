//DFA builder

//This function returns a transition funciton
//for the specified transitionTable.
exports.makeDelta = function (transitionTable){
    return function(state, letter){
      return transitionTable[state][letter];
    }
}

exports.makeDeltaHat = function(transitionTable){
  var self = this;
  this.delta = exports.makeDelta(transitionTable);

  return function(state, arrayOfLetters){
    var nextState = state;
    for(var index in arrayOfLetters){
      nextState = self.delta(nextState, arrayOfLetters[index]);
    }
    return nextState;
  }
}

exports.DFA = function(transitionTable, startState, finalStates){
  var self = this;
  this.startState = startState;
  this.currentState = startState;
  this.finalStates = finalStates;
  //this.delta = exports.makeDelta(transitionTable); //delete this stoopid fuck later. Its a redundant ignorant dick-ass.
  this.deltaHat = exports.makeDeltaHat(transitionTable);
  this.isFinal = function(){
    return self.finalStates.includes(self.currentState);
  }

}
