<?php

/*
 * Created on 22-Sep-10
 */

class ShowFlexpaper {

  private $pid = NULL;

  function ShowFlexpaper($pid) {
    $this->pid = $pid;
  }

  function loadFlexpaper() {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');

    $item = new Fedora_Item($this->pid);
    $datastreams = $item->get_datastreams_list_as_array();

    if( array_key_exists('FLEXPAPER', $datastreams) ) {

      global $base_url;

      $swfURL = $base_url . '/fedora/repository/' . $this->pid . '/FLEXPAPER/FLEXPAPER.swf';
      //FLEXPAPER is the datastream id
      $path = drupal_get_path('module', 'Fedora_Repository');
      $fullPath = base_path() . $path;
      $content = "";
      $pathTojs = "sites/all/libraries/flexpaper/js/flexpaper_flash.js";

      drupal_add_js("$pathTojs");
      //swfobject.js is being loaded from swftools module but we are adding the path to js/flexpaper_flash.js as it is needed as well
      drupal_add_js("sites/all/libraries/swfobject/swfobject.js");
      $content .= '<div id="flashContent"><a href="http://www.macromedia.com/go/getflashplayer">Get the Flash Player</a> to see this player.</div>';

      drupal_add_js('var swfVersionStr = "10.0.0";
              <!-- To use express install, set to playerProductInstall.swf, otherwise the empty string. -->
              var xiSwfUrlStr = "/sites/all/libraries/flexpaper/js/swfobject/expressInstall.swf";

              var flashvars = {
                  SwfFile : escape("' . $swfURL . '"),
            Scale : 0.6,
            ZoomTransition : "easeOut",
            ZoomTime : 0.5,
              ZoomInterval : 0.1,
              FitPageOnLoad : false,
              FitWidthOnLoad : true,
              PrintEnabled : true,
              FullScreenAsMaxWindow : false,
              ProgressiveLoading : true,

              PrintToolsVisible : true,
              ViewModeToolsVisible : true,
              ZoomToolsVisible : true,
              FullScreenVisible : true,
              NavToolsVisible : true,
              CursorToolsVisible : true,
              SearchToolsVisible : true,

              localeChain: "en_US"
            };

         var params = {

            }
             params.quality = "high";
              params.bgcolor = "#ffffff";
              <!--params.allowscriptaccess = "sameDomain";-->
              params.allowfullscreen = "true";
              var attributes = {};
              attributes.id = "FlexPaperViewer";
              attributes.name = "FlexPaperViewer";
              swfobject.embedSWF(
                  "' . $base_url . '/sites/all/libraries/flexpaper/FlexPaperViewer.swf", "flashContent",
                  "800", "600",
                  swfVersionStr, xiSwfUrlStr,
                  flashvars, params, attributes);
    swfobject.createCSS("#flashContent", "display:block;text-align:left;");', 'inline', 'header');


      $tabset = array();
      $tabset['flexpaper_tab'] = array(
        '#type' => 'tabpage',
        '#title' => t('View Document'),
        '#weight' => -1,
        '#content' => $content,
      );

      //$collection_fieldset = array(
      //  '#title' => t($this->pid),
      //  '#collapsible' => TRUE,
      //  '#collapsed' => FALSE,
      //  '#value' => $content);
      //return theme('fieldset', $collection_fieldset);
      return $tabset;
    }
    
    return array();
  }

}

