var getCookie = function(str) {return '';}
var html_str;
var mhss = 'p1.xiaoshidi.net';
var document = {
    write: function(str) {
        html_str = str;
    }
}
var $ = function(name) {
    return {
        html: function(str) {
            html_str = str;
        }
    }
}

function decodeBase64(value) {
    var utf8ByteArray = Base64Utils.b64ToByteArray(Base64Utils.cleanupBase64(value));
    return Base64Utils.decodeFromUtf8Array(utf8ByteArray);
}
