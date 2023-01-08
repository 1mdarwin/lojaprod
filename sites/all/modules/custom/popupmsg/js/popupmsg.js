(function($) {
  Drupal.behaviors.popupmsg = {
    attach: function (context, settings) {
      //alert(settings.place2pay.order_id);

      var message = settings.popupmsg.message;
      var logo = settings.popupmsg.logo;

      $( "body" ).prepend( '<div class="after-login-popup" data-popup="after-login-popup-1"><div class="after-login-popup-inner"><p>' + logo + message + '</p><a class="after-login-popup-close" data-popup-close="after-login-popup-1" href="#">x</a></div></div>' );
      $('.after-login-popup').fadeIn(350);      
      
      $('.after-login-popup').delay(4000).fadeOut('slow'); //Disappear DIV
      $('[data-popup-close]').on('click', function(e)  {
      	var targeted_popup_class = jQuery(this).attr('data-popup-close');
      	$('[data-popup="' + targeted_popup_class + '"]').fadeOut(350);
      	e.preventDefault();
       });
    }
  };
})(jQuery);



