
var common = {
    isMove: false,
    TimerShow: null,
    isEffectEnd: false,
    curPngIndex: 0,
    isMoveEnd: true,
    isDefaultMoveEnd: true,
    key: "a0845e4f6b011cda8ceba737c85c251e",
    iv: "3c7d5684e36b6c65c1e256d37640d73d"
};
common.decrypt = function(code, page) {
    function b(i) {
        var h = CryptoJS.AES.decrypt(i, CryptoJS.enc.Utf8.parse(common.key), {
            iv: CryptoJS.enc.Utf8.parse(common.iv),
            mode: CryptoJS.mode.CBC,
            padding: CryptoJS.pad.Pkcs7
        });
        return h.toString(CryptoJS.enc.Utf8)
    }
    var g = [-1];
    var f = "";
    f = code;
    for (var a = 0; a < f.length; a++) {
        if (f[a] == ",") {
            g.push(a)
        }
    }
    var e = page;
    var d = (f.substring(g[e] + 1, g[e + 1]));
    return new Array(b(d), g.length)
};
common.decryptCode = function(code) {
    var h = CryptoJS.AES.decrypt(code, CryptoJS.enc.Utf8.parse(common.key), {
        iv: CryptoJS.enc.Utf8.parse(common.iv),
        mode: CryptoJS.mode.CBC,
        padding: CryptoJS.pad.Pkcs7
    });
    return h.toString(CryptoJS.enc.Utf8)
}