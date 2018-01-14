const dfaFactory = require("./dfa.js");
const fs = require('fs');

//Create a state machine that recognizes a string that has the substring 010.
const table010 = {
	nothing:["sawZero","nothing"],
	sawZero:["sawZero","sawZeroOne"],
	sawZeroOne:["sawZeroOneZero","nothing"],
	sawZeroOneZero:["sawZeroOneZero","sawZeroOneZero"]
}

const dfaTable010 = new dfaFactory.DFA(table010, 'nothing', ['sawZeroOneZero']);
//---------------------------------------------------------------------------------
//Create a state machine that recognizes a string in which the number of 1's is a multiple of three.
const table111 = {
	nothing:["nothing","sawOne"],
	sawOne:["sawOne","sawOneBlahOne"],
	sawOneBlahOne:["sawOneBlahOne","sawOneBlahOneBlahOne"],
	sawOneBlahOneBlahOne:["sawOneBlahOneBlahOne","sawOne"]
}

const dfaTable111 = new dfaFactory.DFA(table111, 'nothing', ['sawOneBlahOneBlahOne']);
//---------------------------------------------------------------------------------
//Create a state machine that recognizes a string in which the number of 1's is a multiple of three.
//I realize there is a way better way of doing this
const table00111 = {
	nothing:["sawZero","sawOne"],
	sawZero:["sawZeroZero","sawZeroOne"],
	sawOne:["sawZeroOne","sawOneOne"],

	sawZeroZero:["sawZero","sawZeroZeroOne"],
	sawZeroOne:["sawZeroZeroOne","sawZeroOneOne"],
	sawOneOne:["sawZeroOneOne","sawOneOneOne"],

	sawZeroZeroOne:["sawZeroOne","sawZeroZeroOneOne"],
	sawZeroOneOne:["sawZeroZeroOneOne","sawZeroOneOneOne"],
	sawOneOneOne:["sawZeroOneOneOne","sawOne"],

	sawZeroZeroOneOne:["sawZeroOneOne","sawZeroZeroOneOneOne"],
	sawZeroOneOneOne:["sawZeroZeroOneOneOne","sawZeroOne"],
	sawZeroZeroOneOneOne:["sawZeroOneOneOne","sawZeroZeroOne"]
}

const dfaTable00111 = new dfaFactory.DFA(table00111, 'nothing', ['sawZeroZeroOneOneOne']);


console.log("State Machine One--")
console.log("input( 111001001 )");
console.log(dfaTable010.process([1,1,1,0,0,1,0,1,0]));
dfaTable010.reset();
console.log("input( 111001101 )");
console.log(dfaTable010.process([1,1,1,0,1,1,0,1]));
dfaTable010.reset();
console.log("\n");

console.log("State Machine Two--")
console.log("input(111)");
console.log(dfaTable111.process([1,1,1]));
dfaTable111.reset();
console.log("input(1111)");
console.log(dfaTable111.process([1,1,1,1]));
dfaTable111.reset();
console.log("\n");

console.log("State Machine Three--")
console.log("input(010001110011)");
console.log(dfaTable00111.process([0,1,0,0,0,1,1,1,0,0,1,1]));
dfaTable00111.reset();
console.log("input(011011)");
console.log(dfaTable00111.process([0,1,1,0,1,1]));
dfaTable00111.reset();
console.log("\n");


console.log("RegEx ");
//Regular Expression file
function readFinish(err, data){
	if(err){
   console.log(err);
  } else {
   //do stuff
	 function formater(aString){
		 var ret = "warning: "+aString.match(/.+[^:]/)+"\n";
		 return ret;
	 }
	 function arrayToString(prev,curr){
		 return prev+curr;
	 }
	 function reformat(array){

	 }
	 var array = data.match(/[a-zA-z]+(\/[a-zA-Z]+\/)+[a-zA-z0-9\.]+:[0-9]+/g);
	 var writeString = array.map(formater).reduce(arrayToString,"");
	 fs.writeFile('./new', writeString);
	 console.log("Wrote to file './new'");
  }
}

fs.readFile('./mklog', 'utf-8', readFinish);
