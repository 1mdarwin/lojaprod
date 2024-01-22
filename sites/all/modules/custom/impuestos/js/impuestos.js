(function ($) {
  
  Drupal.theme.prototype.impExampleButton = function (path, title) {
    // Create an anchor element with jQuery.
    return $('<a href="' + path + '" title="' + title + '">' + title + '</a>');
  };

  
  Drupal.behaviors.impBehavior = {
    attach: function (context, settings) {
      // By using the 'context' variable we make sure that our code only runs on
      // the relevant HTML. Furthermore, by using jQuery.once() we make sure that
      // we don't run the same piece of code for an HTML snippet that we already
      // processed previously. By using .once('foo') all processed elements will
      // get tagged with a 'foo-processed' class, causing all future invocations
      // of this behavior to ignore them.
      $('.some-selector', context).once('foo', function () {
        // Now, we are invoking the previously declared theme function using two
        // settings as arguments.
        var $anchor = Drupal.theme('impExampleButton', settings.myExampleLinkPath, settings.myExampleLinkTitle);

        // The anchor is then appended to the current element.
        $anchor.appendTo(this);
      });
      //$('#edit-cedula').addClass('solo-numero');
      
      /*$('#edit-cedula').keyup(function (){
            this.value = (this.value + '').replace(/[^0-9+\-Ee.]/g, '');

          });*/
      $('#edit-nombres').keyup(function (){
            this.value = (this.value + '').replace(/[^A-Z a-z+\-Ee.]/g, '');
          });
      
    }
  };

})(jQuery);
