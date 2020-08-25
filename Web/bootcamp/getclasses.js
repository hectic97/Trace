var allClasses = [];
var ParentClasses = [];
var allElements = document.querySelectorAll('*');

for (var i = 0; i < allElements.length; i++) {
  var classes = allElements[i].className.toString().split(/\s+/);
  for (var j = 0; j < classes.length; j++) {
    var cls = classes[j];
    if (cls && allClasses.indexOf(cls) === -1)
      allClasses.push(cls);
  }
}
for (var i = 0; i < allClasses.length; i++) {
  ParentClasses.push($('.'+allClasses[i]).parent().attr('class'));}
console.log(allClasses);
console.log(ParentClasses);