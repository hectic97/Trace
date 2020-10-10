var contextMenuItem = {
    "id": "spendMoney",
    "title": "SpendMoney",
    "contexts": ["selection"],

};
chrome.contextMenus.create(contextMenuItem)

// chrome.contextMenus.onClicked.addListener(fucntion(clickData){
//     if (clickData.menuItemid == "spend"){

//     }
// })