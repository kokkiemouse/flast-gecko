let changeColor = document.getElementById('changeColor');

var url
browser.tabs.query({'active': true, 'lastFocusedWindow': true}, function (tabs) {
    url = tabs[0].url;
});

$(function(){
    $.ajax({
        url:'https://u.artspin.jp/p.php',
        type:'GET',
        data:{'url':url}
    }).done((data)=>{
        execCopy(data);
        $('.m-url').text(data)
        $('.url').text(url)
        $('.qr').qrcode({width: 150, height: 150, text: data});
        $('.qr').qrcode({width: 150, height: 150, text: url});
        $('.share').append('<a class="link" href="https://getpocket.com/edit?url='+data+'"><img src="http://www.google.com/s2/favicons?domain=getpocket.com"></a>');
        $('.share').append('<a class="link" href="http://b.hatena.ne.jp/add?&url='+data+'"><img src="http://www.google.com/s2/favicons?domain=b.hatena.ne.jp"></a>');
        $('.share').append('<a class="link" href="https://social-plugins.line.me/lineit/share?url='+data+'"><img src="http://www.google.com/s2/favicons?domain=line.me"></a>');
        $('.share').append('<a class="link" href="https://twitter.com/intent/tweet?text='+document.title+'&url='+data+'"><img src="http://www.google.com/s2/favicons?domain=twitter.com"></a>');
        

        $(".share").on("click",".link",function (e) {
                console.log($(e.currentTarget).attr('href'));
                
                browser.tabs.create({ url: $(e.currentTarget).attr('href') });
            
        });
    }).fail((data)=>{

    }).always((data)=>{

    });

    $('.m-url').on("click",function () {
        execCopy($(this).text())
        $(".title").html("短縮URLを<br>クリップボードに<br>コピーしました")
    });
    $('.url').on("click",function () {
        execCopy($(this).text());
        $(".title").html("非短縮URLを<br>クリップボードに<br>コピーしました")

    });
});
function execCopy(string){
    var tmp=document.createElement("div");
    var pre=document.createElement('pre');
    pre.style.webkitUserSelect='auto';
    pre.style.userSelect='auto';
    tmp.appendChild(pre).textContent=string;
    var s=tmp.style;s.position='fixed';
    s.right='200%';
    document.body.appendChild(tmp);
    document.getSelection().selectAllChildren(tmp);
    var result=document.execCommand("copy");
    document.body.removeChild(tmp);
    return result;
}
