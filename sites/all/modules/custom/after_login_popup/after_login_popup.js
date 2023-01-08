( function( $ ) {

    $(document).ready(function() {

        var title = Drupal.settings.after_login_popup.login_title;
        var text = Drupal.settings.after_login_popup.login_text;
        var message = Drupal.settings.after_login_popup.message;
        var logo = Drupal.settings.after_login_popup.logo;
     
        $( "body" ).prepend( '<div class="after-login-popup" data-popup="after-login-popup-1"><div class="after-login-popup-inner"><h2>' +  logo + '</h2><p>' + message + '</p><p><a data-popup-close="after-login-popup-1" href="#">Cerrar</a></p><a class="after-login-popup-close" data-popup-close="after-login-popup-1" href="#">x</a></div></div>' );
        $('.after-login-popup').fadeIn(350); 
	$('.after-login-popup').delay(3000).fadeOut('slow'); // Dissapear DIV
    
        $('[data-popup-close]').on('click', function(e)  {
            var targeted_popup_class = jQuery(this).attr('data-popup-close');
            $('[data-popup="' + targeted_popup_class + '"]').fadeOut(350);
            e.preventDefault();
        });
   
    });      
    
} )( jQuery );
