/* javascript used by www.dlugosz.com/Repertoire/refman/
   Copyright 2004 by John M. Dlugosz
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

function checkframe (indexurl)
 {
 var params= new Object;
 if (get_params (window, params)) {
    if (params.param1 == "NOFRAMES") return;  //don't change anything.
    else alert ("invalid parameter " + params.param1 + " ignored.");
    }
 if (name != "info" && name != "footer") {
    var infoURL= location.href;
    // make the URL relative to this location.
    var pos= infoURL.indexOf ('/Tomahawk/');
    if (pos < 0)  pos= infoURL.indexOf ('/RatWin/');
    if (pos < 0)  pos= infoURL.indexOf ('/Classics/');
    if (pos > 0)
       infoURL= infoURL.slice (pos+1);
       // else just leave it the way it was.
    var newURL= "../makeframe.html?" + infoURL + '+' + indexurl;
    location.href= newURL;
    }
 }

