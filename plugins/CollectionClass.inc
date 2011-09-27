<?php

class JWACollectionClass extends CollectionClass {
  
  function showFieldSets($page_number) {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');

    global $base_url;

    $tabset = array();

    global $user;
    $objectHelper = new ObjectHelper();
    $item = new Fedora_Item($this->pid);
    $query = NULL;
    if ($item->exists() && array_key_exists('QUERY', $item->datastreams)) {
      $query = $item->get_datastream_dissemination('QUERY');
    }
    $results = $this->getRelatedItems($this->pid, $query);

    $base_path = base_path();
    $path = $base_path . drupal_get_path('module','fedora_repository');
    if (user_access('add fedora datastreams')) {
      $collection_items = "<a href='$base_url/formbuilder/ingest/$this->pid'><img alt='ingest' src='$path/images/48px-Crystal_Clear_app_download_manager.png'/>Add<p></a>";
    }
    $collection_items .= $this->renderCollection($results, $this->pid, NULL, NULL, $page_number);
    $collection_item = new Fedora_Item($this->pid);

    // Check the form post to see if we are in the middle of an ingest operation.
    $show_ingest_tab = (!empty($_POST['form_id']) && $_POST['form_id'] == 'islandora_form_builder_ingest_form');
    $add_to_collection = $this->getIngestInterface();

    $tabset['view_tab'] = array(
      '#type' => 'tabpage',
      '#title' => 'View',
      '#weight' => -2,
      '#selcted' => !$show_ingest_tab,
      '#content' => $collection_items
    );

    //$tabset['add_tab'] = array(
      // #type and #title are the minimum requirements.
    //  '#type' => 'tabpage',
    //  '#title' => t('Add Object'),
    //  '#selected' => $show_ingest_tab,
    //  // This will be the content of the tab.
    //  '#content' => drupal_get_form('islandora_form_builder_ingest_form', $this->pid),
    //  //'#ajax_url' => url('formbuilder/ingest/jwa:top'),
    //);
    
    return $tabset;
  }

}

