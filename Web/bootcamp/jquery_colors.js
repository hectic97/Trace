
var h2tagman = {
    setColor:function(color){
    // var alist = document.querySelectorAll('h2');
    // var i = 0;
    // while(i<alist.length){
    //     alist[i].style.color = color;
    //     i++;
    $('h2').css('color', color);
    } 
}

var Body = {
    setColor:function(color){
    // document.querySelector('body').style.color = color;
    $('body').css('color',color);
    },
    setBackgroundColor:function(color){
    // document.querySelector('body').style.backgroundColor = color;
    $('body').css('background-color', color);
    }
}


function nightDayHandler(self){
    var target = document.querySelector('body');
    if(self.value === 'night'){
        Body.setBackgroundColor('black');
        Body.setColor('white');
        self.value = 'day';
        h2tagman.setColor('crimson');
        
    }
    else{
        Body.setBackgroundColor('white');
        Body.setColor('black');
        self.value = 'night';
        h2tagman.setColor('blue');

    }
            
}
