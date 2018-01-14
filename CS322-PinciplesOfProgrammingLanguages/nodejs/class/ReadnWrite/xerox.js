const fs = require('fs');

function readFinish(err, data){
  if(err){
    console.log(err);
  } else {
    fs.writeFile('./copy.txt', data);
  }
}

fs.readFile('./source.txt', 'utf-8', readFinish);
