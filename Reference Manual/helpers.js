/* javascript used by www.dlugosz.com/Repertoire/refman/
   Copyright 2006 by John M. Dlugosz
*/

function get_params (w, result)
 {
 var url= w.document.URL;
 var qpos= url.indexOf ('?');
 if (qpos < 0)  return false;
 var ppos= url.indexOf ('+', qpos+1);
 if (ppos < 0) { // only 1 parameter given
    result.param1= url.slice (qpos+1);
    }
 else {
    result.param1= url.slice (qpos+1, ppos); // appears that 'end' parameter is EXCLUSIVE.
    result.param2= url.slice (ppos+1);
    }
 return true;
 }

function is_home_url()
 {
 return location.hostname == "www.dlugosz.com";
 }

function add_nav_button (text, dest, target)
 {
 var div= document.getElementById('navbar');
 if (!div)  return;
 alert ("I'm here!");     //>> not loaded yet.  Just add to array for delayed processing.
 div.textContent= text + ", " + dest + ", " + target;  //just testing
 }


function URL_relative (URL)
 {
 var pos= URL.indexOf ('/Tomahawk/');
 if (pos < 0)  pos= URL.indexOf ('/RatWin/');
 if (pos < 0)  pos= URL.indexOf ('/Classics/');
 if (pos > 0)
    URL= URL.slice (pos+1);
    // else just leave it the way it was.
 return URL;
 }

function checkframe (indexurl)
 {
 window.document.checkframe_installed= indexurl;
 var params= new Object;
 if (get_params (window, params)) {
    if (params.param1 == "NOFRAMES")  return;  //don't change anything.
    else alert ("invalid parameter " + params.param1 + " ignored.");
    }
 if (name != "info" && name != "footer") {
    var infoURL= URL_relative (location.href);
    var newURL= "../makeframe.html?" + infoURL + '+' + indexurl;
    location.href= newURL;
    }
 }


function within_book (alink)
// is this <A HREF> within the overall book (true) or external (false)
 {
 return true;  // stub for now.
 }


function deframe_1_link (thislink)
 {
 var targ= thislink.target;
 if (targ == 'info' || targ=='footer' || targ=='index')  {
    thislink.target="";
    if (within_book(thislink)) {
       if (thislink.search == "") thislink.href += "?NOFRAMES";
       }
    }
 }

function deframe_links (doc)
 {
 if (document.evaluate) {
    var allLinks= document.evaluate ('//a[@href]', doc, null, XPathResult.UNORDERED_NODE_SNAPSHOT_TYPE, null);
    for (var i = 0; i < allLinks.snapshotLength; i++) {
       deframe_1_link (allLinks.snapshotItem(i))
       }
    }
 else if (document.selectNodes) {  // for IE6
    var list= document.selectNodes ('//a[@href]');
    for (var i= 0; i < list.length; ++i)  deframe_1_link (list[i]);
    }
 }

function index_load()
 {
 if (document.location.search == "?NOFRAMES" || document == top.document) {
    deframe_links (document);
    // offer to add frames
    var el= document.createElement ("P");
    el.className="frameoffer";
    var link= document.createElement ("A");
    el.appendChild (link);
    link.textContent= "Click to add navigation frames.";
    document.body.insertBefore (el, document.body.firstChild);
    var relpath= "";  // >> find relative path
    var destURL= relpath + "makeframe.html?documentation_info.html#toptop+" + URL_relative(document.location.href);
    link.href= destURL;
    }
 }

function adjustIFrameSize (iframeWindow)
 {
 var iframeElement = document.getElementById (iframeWindow.frameElement.id);
 var height= iframeWindow.document.height;  // DOM Level 0
 if (!height)  height= iframeWindow.document.body.clientHeight;  // Introduced by IE
 if (!height) return;
 // convert px to em
 var suffix= "px";  // fallback if can't figure it out
 var style;
 if (window.getComputedStyle) style= window.getComputedStyle (iframeElement,"");
 else style= iframeElement.currentStyle;
 if (style) {  // so far so good
    var oneline= style.fontSize;  // e.g. 20px
    var onelinenum= oneline.substring (0, oneline.length-2);
    height= (height+1) / onelinenum;
    suffix= "em";
    }
 // set the result
 iframeElement.style.height= height + suffix;
 }

function set_text (node, s)
 {
 node.textContent= s;
 node.innerText= s;  // one of these is right
 }

