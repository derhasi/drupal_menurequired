// $Id$

/**
 * Implements Jquery UI Tabs in input formats.
 */

/**
 * Attaches the ahah behavior to each ahah form element.
 */
Drupal.behaviors.jaueryui_filter_tabs = function(context) {
  for (var i in Drupal.settings.jqueryui_filter_tabs) {
    var tabs_class = Drupal.settings.jqueryui_filter_tabs[i];
    $('div.jqueryui-filter-tabs.' + tabs_class + ':not(.jqueryui-filter-tabs-processed)').each(function () {
      $(this).tabs();
      $(this).addClass('jqueryui-filter-tabs-processed');
    });
  }
};