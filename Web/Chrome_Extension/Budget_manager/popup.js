$(function(){
    chrome.storage.sync.get(['total','limit'],function(budget){
        $('#total').text(budget.total);
        $('#limit').text(budget.limit);
    });

    $('#aa').click(function(){
        chrome.windows.create({url:"popup.html",
        type: "popup"});
        
    })
    $('#spendAmount').click(function(){
        chrome.storage.sync.get(['total','limit'],function(budget){
            var newTotal = 0;
            if (budget.total){
                newTotal += parseInt(budget.total);
            }
            var amount = $('#amount').val();
            if(amount){
                newTotal += parseInt(amount);
            }
            chrome.storage.sync.set({'total':newTotal},function(){
                if (amount && newTotal >= budget.limit){
                    var notifOptions = {
                    type: 'basic',
                    iconUrl: 'money.png',
                    title: 'Limit Reached!',
                    message: "STOP! Looks like you've reached your limit",
                    priority: 1
                };
                chrome.notifications.create('limitNotif',notifOptions);
            }
            });

            $('#total').text(newTotal);
            $('#amount').val('');
        })
    })
})