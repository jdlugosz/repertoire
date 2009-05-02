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

function deframe_links (doc)
 {
 var allLinks= document.evaluate ('//a[@href]', doc, null, XPathResult.UNORDERED_NODE_SNAPSHOT_TYPE, null);
 for (var i = 0; i < allLinks.snapshotLength; i++) {
    var thislink = allLinks.snapshotItem(i);
    var targ= thislink.target;
    if (targ == 'info' || targ=='footer' || targ=='index')  thislink.target="";
    if (within_book(thislink)) {
       if (thislink.search == "") thislink.href += "?NOFRAMES";
       }
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

