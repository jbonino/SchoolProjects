const dfaFactory = require("./DFA.js");

const sandwichTable = {
  nothing:["black hole","1-"],
  blackHole:["black hole","black hole"],
  "1-":["black hole","11-"],
  "11-":["11-","11*1-"],
  "11*1-":["11-","11*11-"],
  "11*11-":["11-","11*11-"]
}

const sandwichMachine = dfaFactory.makeDelta(sandwichTable);
const sandwichMachineHat = dfaFactory.makeDeltaHat(sandwichTable);
const sandwichDFA = new dfaFactory.DFA(sandwichTable, 'nothing', ['11*11-']);

console.log(sandwichMachine('1-',1));
console.log(sandwichMachineHat('nothing', [1,1,0,1,0,1,1]));
