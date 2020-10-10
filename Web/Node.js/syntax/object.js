var members= ['a','b'];
var roles = {'programmer':'c',
'designer':'d'}
console.log(roles.designer);
var i = 0;
while(i<members.length)
{
    console.log('loop',members[i]);
    i++;
}
for(var name in roles){
    console.log('object =>',name);
    console.log('value =>',roles.name); // roles[name];
}

var f= function f1(){
    console.log('Hello, World!');
}
console.log(f);

var a = [f];
a[0](); //a[0] = f = function f1(){};
var o = { func:f}
o.func();

var v1 = 'v1';
var v2 = 'v2';

var obj = {
    v1 : 'v1',
    v2 : 'v2', // like folder
    f1 : function(){
        console.log(this.v1);},
    f2 : function(){
        console.log(this.v2);}
    
}

// function fv1(){
//     console.log(o.v1);
// }
// function fv2(){
//     console.log(o.v2);
// }
obj.f1();
obj.f2();