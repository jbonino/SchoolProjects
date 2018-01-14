
//The function makeDelta() returns a transition
// function for the specified transition table.
exports.makeDelta = function (transitionTable){
	return function(state, letter){
		return transitionTable[state][letter];
	}
}

//The function makeDeltaHat()
exports.makeDeltaHat = function(transitionTable){
	const delta = exports.makeDelta(transitionTable);
	const deltaReduce = function(prev,curr){return delta(prev, curr);};
	return function(state, arrayOfLetters){
		return arrayOfLetters.reduce(deltaReduce, state);
	}
}

//This is the constructor for a state machine.
//   It's public methods are,
//		reset()  	"reset the state machine"
//		isFinal()  "answer true if the machine is in a final state"
//		process(arrayOfLetters)	"answer true if the letters were accepted"
exports.DFA = function(transitionTable, startState, finalStates){
	// Private
	var currentState = startState;
	var finalStates = finalStates;
	const deltaHat = exports.makeDeltaHat(transitionTable);
	var self = this;

	// Public
	this.isFinal = function(){return finalStates.indexOf(currentState) != -1;}
	this.reset = function(){ currentState = startState; }


	this.process = function(inputArray){
		currentState = deltaHat(currentState, inputArray);
		return self.isFinal();
	}
}
