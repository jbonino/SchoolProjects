function incrementer(delta){
	if(arguments.length == 0) delta = "0";
	return function(arg){
		if(arguments.length == 0) return delta;
		if(delta)
		return arg+delta;
	}
}

function rms(){
	var doubleTotal=0;
	if(arguments.length == 0) return null;
	for(var i=0;i<arguments.length;i++){
		doubleTotal= (arguments[i]*arguments[i])+doubleTotal;
	}
	return Math.sqrt(doubleTotal/arguments.length);
}

function Student(first, last, major){
	this.first = first || "no name";
	this.last = last || "no last name";
	this.major = major || "no major specified";
	this.last = last || "no last n";
	this.last = last || "no last n";

	return last+", "+first;
}
console.log("");
console.log("Test incrementer");

var my7inc = incrementer(7);
console.log(my7inc(4));
var my0inc = incrementer();
console.log(my0inc());


console.log(rms(1,2,3,4));
console.log(rms());




var myStudent = new Student("Jane", "Doe", "Anthropology");
//console.log(myStudent.stringify());
