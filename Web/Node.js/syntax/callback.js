// function a()
// {
//     console.log('A');
// }

var a = function(){   //noname func
    console.log('A');
}

function slowfunc(callback){
    callback();
}

slowfunc(a);