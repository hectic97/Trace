const request = require('request')
const NAVER_CLIENT_ID = 'AAS3h2TUckshmQkUQJvO';
const NAVER_CLIENT_SECRET = 'PEt0Fkzb3g';
var api_url = 'https://openapi.naver.com/v1/datalab/shopping/category/age';
var request_body = {
        "startDate": "2017-08-01",
        "endDate": "2017-09-30",
        "timeUnit": "month",
        "category": "50001466",
        "device": "pc",
        "gender": "m",
        "ages": [ "20",  "30"]
      }
request.post({
    url: api_url,
    body: JSON.stringify(request_body),
    headers: {
        'X-Naver-Client-Id': NAVER_CLIENT_ID,
        'X-Naver-Client-Secret': NAVER_CLIENT_SECRET,
        'Content-Type': 'application/json'
    }
},
function (error, response, body) {
    console.log(response.statusCode);
    console.log(body);
});