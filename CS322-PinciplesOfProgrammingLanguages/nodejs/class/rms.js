funciton rms( arrayOfNumbers ){
  function squareIt(num){
    return num*num;
  }
  function sumThem(prev, curr){
    return prev + curr;
  }

  function sumOfSquares( arrayOfNumbers ){
    return arrayOfNumbers.map(squareIt).reduce(sumThem,0);
  }
  return Math.sqrt(sumOfSquares(arrayOfNumbers)/arrayOfNumbers.length);
}
