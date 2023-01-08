/*(function($) {
  Drupal.behaviors.place2pay = {
    attach: function (context, settings) {
      alert("Hola mundito");
      $.cookie("testName", "Test Name",{ expires : 365, path: "/;SameSite=None"});
      //alert(settings.place2pay.processUrl);
      //P.init(settings.place2pay.processUrl);        
    }
  };
})(jQuery);
*/
document.cookie="SameSite=None;expires=Fri, 31 Dec 9999 23:59:59 GMT;domain=https://servicios.axiscloud.ec;path=/infracciones;SameSite=None";
document.cookie="axis="+0+";Domain=.servicios.axiscloud.ec; path=/ConsultaInfracciones/paginas; SameSite=None; Secure"
alert( document.cookie );

