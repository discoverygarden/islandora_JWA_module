<?php

class SWFAudioPlayer {

  private $pid = NULL;

  function __construct($pid) {
    $this->pid = $pid;
  }

  function showMP3() {

    global $base_url;
    $playlist = $base_url . '/fedora/repository/' . $this->pid . '/PLAYLIST/playlist.xml';

    //PROXY_MP3 is the datastream id
    $path = drupal_get_path('module', 'islandora_JWA_module');
    $fullpath = base_path() . $path;

    drupal_add_js($path . '/jwplayer/jwplayer.js');
    drupal_add_js($path . '/jwplayer/swfobject.js');

    $content = '<video id="flashContent"><a href="http://www.macromedia.com/go/getflashplayer">Get the Flash Player</a> to see this player.</video>';

    //var flashvars = { file:escape("$swfURL"),image:escape("$swfImageURL"),autostart:'false' };

    $js_string = <<<ENDJS

var swfVersionStr = "10.0.0";
var flashvars = {
      'playlistfile':   escape("$playlist"),
      'playlist.position':      'right',
      'playlist.size':  '115',
       repeat: "list",
   };
var params = { allowfullscreen:'false', allowscriptaccess:'false' };
var attributes = { id:'AudioViewer', name:'AudioViewer' };

swfobject.embedSWF('$fullpath/jwplayer/player.swf','flashContent','400','200','9.0.115','false',flashvars, params, attributes);
swfobject.createCSS("#flashContent", "display:block;text-align:left;");
ENDJS;
    drupal_add_js($js_string, 'inline', 'header');

    $tabset['first_tab'] = array(
      '#weight' => -1,
      '#type' => 'tabpage',
      '#title' => t('Listen'),
      '#content' => $content,
    );

    return $tabset;
  }

}

