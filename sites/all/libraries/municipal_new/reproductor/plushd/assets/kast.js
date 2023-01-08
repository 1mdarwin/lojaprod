(function($,window,document,undefined){var defaults={host:'',port:80,protocol:'http',version:2,sid:1,statsPath:'stats',playedPath:'played',directStreamURL:false,ui:'colored',theme:'light',colors:{primary:'cyan',accent:'yellow'},startTemplate:'maximized',position:'right',container:'body',autoPlay:false,autoUpdate:true,artwork:true,statusBar:true,minimizeMaximize:true,muteUnmute:true,startMuted:false,serverInfo:true,serverInfo2:true,serverInfo3:true,oyentesInfo:true,played:true,currentTrack:true,currentArtist:true,playedTracks:true,playedArtists:true,offlineCheck:true,language:{offlineText:'Temporarily Offline',playedText:'Played',unknownTrackText:'Unknown Track - c^o^d^e^l^i^s^t^.^c^c',unknownArtistText:'Unknown Artist'},mobileCare:true,irrelevantWords:['feat.','ft.','Feat.','Ft.'],overHTTPS:false,direct:false,betaProxies:false,continuous:true,onReady:function(){},onAudioLoad:function(){},onMobile:function(){},onPlay:function(){},onPause:function(){},onStop:function(){},onMinimize:function(){},onMaximize:function(){},onMute:function(){},onUnmute:function(){},onUpdate:function(){},onUpdateAll:function(){},onOffline:function(){},onOnline:function(){},onCurrentArtwork:function(){},onPlayedArtworks:function(){},onCurrentInfo:function(){},onPlayedInfo:function(){},onDynamicColors:function(){},onDynamicColorsContrast:function(){},onDynamicTheme:function(){}};function Plugin(element,options){this.opt=$.extend({},defaults,options);var HTML5Audio=function(){var a=new Audio();return!!((a.canPlayType)&&(a.canPlayType('audio/mpeg;').replace(/^no$/,'')||a.canPlayType('audio/ogg; codecs="vorbis"').replace(/^no$/,'')||a.canPlayType('audio/ogg; codecs="opus"').replace(/^no$/,'')||a.canPlayType('audio/aac;').replace(/^no$/,'')));}
if(!this.opt.host||!HTML5Audio||!window.DOMParser||!document.implementation.createHTMLDocument){$.data(document.body,'plugin_kast',null)
throw Error("Kast couldn't load")}
if(options.language){this.opt.language=$.extend({},defaults.language,options.language);}
if(typeof options.colors==='object'){this.opt.colors=$.extend({},defaults.colors,options.colors);}
if(this.opt.startTemplate==='minimized'&&(!this.opt.statusBar||!this.opt.minimizeMaximize)){this.opt.played=false;}
var iot=this.opt;var protocol=(document.location.protocol==='https:')?'https':'http';if(iot.direct&&protocol==='https'){iot.protocol=protocol}
this.host=iot.protocol+'://'+iot.host+':'+iot.port+'/';this.hostCORS=['https://cors-anywhere.herokuapp.com/'+this.host,protocol+'://kastproxy-us.herokuapp.com/'+this.host,protocol+'://kastproxy-eu.herokuapp.com/'+this.host];if(iot.overHTTPS&&protocol==='https:'){this.host=this.hostCORS[0];}
var sc2sid=iot.sid,audioSrc=iot.directStreamURL||((sc2sid>1)?this.host+'stream/'+sc2sid+'/;':this.host+';');this.audio=document.createElement('audio');this.audio.src=audioSrc+'?_='+Math.random();this.audio.load();iot.onAudioLoad(this.audio)
this.mobile=false;this.mobileMedium=false;this.mobileUltra=false;var mC=iot.mobileCare,mCMW=mC[1]||'599px';if(mC&&window.matchMedia&&window.matchMedia('(max-width: '+mCMW+')').matches){this.mobile=true;iot.autoPlay=false;iot.startTemplate='minimized';iot.offlineCheck=false;if(mC[0]==='medium'||mC[0]==='high'||mC[0]==='very high'||mC[0]==='ultra'){this.mobileMedium=true;if(iot.autoUpdate==='all'){iot.autoUpdate=true}
if(iot.theme==='dynamic'){iot.theme='light'}
if(iot.colors==='dynamic'){iot.colors=false;}}
if(mC[0]==='high'||mC[0]==='very high'||mC[0]==='ultra'){iot.artwork=iot.played=false;}
if(mC[0]==='very high'||mC[0]==='ultra'){iot.autoUpdate=iot.minimizeMaximize=false;}
if(mC[0]==='ultra'){this.mobileUltra=true;iot.statusBar=iot.serverInfo=iot.currentArtist=iot.currentTrack=false;}
iot.onMobile()}
this.init();}
var CanvasImage=function(image){this.canvas=document.createElement('canvas');this.context=this.canvas.getContext('2d');document.body.appendChild(this.canvas);this.width=this.canvas.width=image.width;this.height=this.canvas.height=image.height;this.context.drawImage(image,0,0,this.width,this.height);},ColorThief=function(){};CanvasImage.prototype={clear:function(){this.context.clearRect(0,0,this.width,this.height);},update:function(imageData){this.context.putImageData(imageData,0,0);},getPixelCount:function(){return this.width*this.height;},getImageData:function(){return this.context.getImageData(0,0,this.width,this.height);},removeCanvas:function(){this.canvas.parentNode.removeChild(this.canvas);}}
ColorThief.prototype.getPalette=function(sourceImage,colorCount){var image=new CanvasImage(sourceImage);var imageData=image.getImageData();var pixels=imageData.data;var pixelCount=image.getPixelCount();var pixelArray=[];for(var i=0,offset,r,g,b,a;i<pixelCount;i=i+10){offset=i*4;r=pixels[offset+0];g=pixels[offset+1];b=pixels[offset+2];a=pixels[offset+3];if(a>=125){if(!(r>250&&g>250&&b>250)){pixelArray.push([r,g,b]);}}}
var cmap=MMCQ.quantize(pixelArray,colorCount);var palette=cmap?cmap.palette():null;image.removeCanvas();return palette;};if(!pv){var pv={map:function(array,f){var o={};return f?array.map(function(d,i){o.index=i;return f.call(o,d);}):array.slice();},naturalOrder:function(a,b){return(a<b)?-1:((a>b)?1:0);},sum:function(array,f){var o={};return array.reduce(f?function(p,d,i){o.index=i;return p+f.call(o,d);}:function(p,d){return p+d;},0);},max:function(array,f){return Math.max.apply(null,f?pv.map(array,f):array);}};}
var MMCQ=(function(){var sigbits=5,rshift=8-sigbits,maxIterations=1000,fractByPopulations=0.75;function getColorIndex(r,g,b){return(r<<(2*sigbits))+(g<<sigbits)+b;}
function PQueue(comparator){var contents=[],sorted=false;function sort(){contents.sort(comparator);sorted=true;}
return{push:function(o){contents.push(o);sorted=false;},peek:function(index){if(!sorted)sort();if(index===undefined)index=contents.length-1;return contents[index];},pop:function(){if(!sorted)sort();return contents.pop();},size:function(){return contents.length;},map:function(f){return contents.map(f);},debug:function(){if(!sorted)sort();return contents;}};}
function VBox(r1,r2,g1,g2,b1,b2,histo){var vbox=this;vbox.r1=r1;vbox.r2=r2;vbox.g1=g1;vbox.g2=g2;vbox.b1=b1;vbox.b2=b2;vbox.histo=histo;}
VBox.prototype={volume:function(force){var vbox=this;if(!vbox._volume||force){vbox._volume=((vbox.r2-vbox.r1+1)*(vbox.g2-vbox.g1+1)*(vbox.b2-vbox.b1+1));}
return vbox._volume;},count:function(force){var vbox=this,histo=vbox.histo;if(!vbox._count_set||force){var npix=0,i,j,k;for(i=vbox.r1;i<=vbox.r2;i++){for(j=vbox.g1;j<=vbox.g2;j++){for(k=vbox.b1;k<=vbox.b2;k++){index=getColorIndex(i,j,k);npix+=(histo[index]||0);}}}
vbox._count=npix;vbox._count_set=true;}
return vbox._count;},copy:function(){var vbox=this;return new VBox(vbox.r1,vbox.r2,vbox.g1,vbox.g2,vbox.b1,vbox.b2,vbox.histo);},avg:function(force){var vbox=this,histo=vbox.histo;if(!vbox._avg||force){var ntot=0,mult=1<<(8-sigbits),rsum=0,gsum=0,bsum=0,hval,i,j,k,histoindex;for(i=vbox.r1;i<=vbox.r2;i++){for(j=vbox.g1;j<=vbox.g2;j++){for(k=vbox.b1;k<=vbox.b2;k++){histoindex=getColorIndex(i,j,k);hval=histo[histoindex]||0;ntot+=hval;rsum+=(hval*(i+0.5)*mult);gsum+=(hval*(j+0.5)*mult);bsum+=(hval*(k+0.5)*mult);}}}
if(ntot){vbox._avg=[~~(rsum / ntot),~~(gsum / ntot),~~(bsum / ntot)];}else{vbox._avg=[~~(mult*(vbox.r1+vbox.r2+1)/ 2),~~(mult*(vbox.g1+vbox.g2+1)/ 2),~~(mult*(vbox.b1+vbox.b2+1)/ 2)];}}
return vbox._avg;},contains:function(pixel){var vbox=this,rval=pixel[0]>>rshift;gval=pixel[1]>>rshift;bval=pixel[2]>>rshift;return(rval>=vbox.r1&&rval<=vbox.r2&&gval>=vbox.g1&&gval<=vbox.g2&&bval>=vbox.b1&&bval<=vbox.b2);}};function CMap(){this.vboxes=new PQueue(function(a,b){return pv.naturalOrder(a.vbox.count()*a.vbox.volume(),b.vbox.count()*b.vbox.volume());});}
CMap.prototype={push:function(vbox){this.vboxes.push({vbox:vbox,color:vbox.avg()});},palette:function(){return this.vboxes.map(function(vb){return vb.color;});},size:function(){return this.vboxes.size();},map:function(color){var vboxes=this.vboxes;for(var i=0;i<vboxes.size();i++){if(vboxes.peek(i).vbox.contains(color)){return vboxes.peek(i).color;}}
return this.nearest(color);},nearest:function(color){var vboxes=this.vboxes,d1,d2,pColor;for(var i=0;i<vboxes.size();i++){d2=Math.sqrt(Math.pow(color[0]-vboxes.peek(i).color[0],2)+
Math.pow(color[1]-vboxes.peek(i).color[1],2)+
Math.pow(color[2]-vboxes.peek(i).color[2],2));if(d2<d1||d1===undefined){d1=d2;pColor=vboxes.peek(i).color;}}
return pColor;},forcebw:function(){var vboxes=this.vboxes;vboxes.sort(function(a,b){return pv.naturalOrder(pv.sum(a.color),pv.sum(b.color));});var lowest=vboxes[0].color;if(lowest[0]<5&&lowest[1]<5&&lowest[2]<5)
vboxes[0].color=[0,0,0];var idx=vboxes.length-1,highest=vboxes[idx].color;if(highest[0]>251&&highest[1]>251&&highest[2]>251)
vboxes[idx].color=[255,255,255];}};function getHisto(pixels){var histosize=1<<(3*sigbits),histo=new Array(histosize),index,rval,gval,bval;pixels.forEach(function(pixel){rval=pixel[0]>>rshift;gval=pixel[1]>>rshift;bval=pixel[2]>>rshift;index=getColorIndex(rval,gval,bval);histo[index]=(histo[index]||0)+1;});return histo;}
function vboxFromPixels(pixels,histo){var rmin=1000000,rmax=0,gmin=1000000,gmax=0,bmin=1000000,bmax=0,rval,gval,bval;pixels.forEach(function(pixel){rval=pixel[0]>>rshift;gval=pixel[1]>>rshift;bval=pixel[2]>>rshift;if(rval<rmin)rmin=rval;else if(rval>rmax)rmax=rval;if(gval<gmin)gmin=gval;else if(gval>gmax)gmax=gval;if(bval<bmin)bmin=bval;else if(bval>bmax)bmax=bval;});return new VBox(rmin,rmax,gmin,gmax,bmin,bmax,histo);}
function medianCutApply(histo,vbox){if(!vbox.count())return;var rw=vbox.r2-vbox.r1+1,gw=vbox.g2-vbox.g1+1,bw=vbox.b2-vbox.b1+1,maxw=pv.max([rw,gw,bw]);if(vbox.count()==1){return[vbox.copy()];}
var total=0,partialsum=[],lookaheadsum=[],i,j,k,sum,index;if(maxw==rw){for(i=vbox.r1;i<=vbox.r2;i++){sum=0;for(j=vbox.g1;j<=vbox.g2;j++){for(k=vbox.b1;k<=vbox.b2;k++){index=getColorIndex(i,j,k);sum+=(histo[index]||0);}}
total+=sum;partialsum[i]=total;}}else if(maxw==gw){for(i=vbox.g1;i<=vbox.g2;i++){sum=0;for(j=vbox.r1;j<=vbox.r2;j++){for(k=vbox.b1;k<=vbox.b2;k++){index=getColorIndex(j,i,k);sum+=(histo[index]||0);}}
total+=sum;partialsum[i]=total;}}else{for(i=vbox.b1;i<=vbox.b2;i++){sum=0;for(j=vbox.r1;j<=vbox.r2;j++){for(k=vbox.g1;k<=vbox.g2;k++){index=getColorIndex(j,k,i);sum+=(histo[index]||0);}}
total+=sum;partialsum[i]=total;}}
partialsum.forEach(function(d,i){lookaheadsum[i]=total-d;});function doCut(color){var dim1=color+'1',dim2=color+'2',left,right,vbox1,vbox2,d2,count2=0;for(i=vbox[dim1];i<=vbox[dim2];i++){if(partialsum[i]>total / 2){vbox1=vbox.copy();vbox2=vbox.copy();left=i-vbox[dim1];right=vbox[dim2]-i;if(left<=right)
d2=Math.min(vbox[dim2]-1,~~(i+right / 2));else d2=Math.max(vbox[dim1],~~(i-1-left / 2));while(!partialsum[d2])d2++;count2=lookaheadsum[d2];while(!count2&&partialsum[d2-1])count2=lookaheadsum[--d2];vbox1[dim2]=d2;vbox2[dim1]=vbox1[dim2]+1;return[vbox1,vbox2];}}}
return maxw==rw?doCut('r'):maxw==gw?doCut('g'):doCut('b');}
function quantize(pixels,maxcolors){if(!pixels.length||maxcolors<2||maxcolors>256){return false;}
var histo=getHisto(pixels),histosize=1<<(3*sigbits);var nColors=0;histo.forEach(function(){nColors++;});if(nColors<=maxcolors){}
var vbox=vboxFromPixels(pixels,histo),pq=new PQueue(function(a,b){return pv.naturalOrder(a.count(),b.count());});pq.push(vbox);function iter(lh,target){var ncolors=1,niters=0,vbox;while(niters<maxIterations){vbox=lh.pop();if(!vbox.count()){lh.push(vbox);niters++;continue;}
var vboxes=medianCutApply(histo,vbox),vbox1=vboxes[0],vbox2=vboxes[1];if(!vbox1){return;}
lh.push(vbox1);if(vbox2){lh.push(vbox2);ncolors++;}
if(ncolors>=target)return;if(niters++>maxIterations){return;}}}
iter(pq,fractByPopulations*maxcolors);var pq2=new PQueue(function(a,b){return pv.naturalOrder(a.count()*a.volume(),b.count()*b.volume());});while(pq.size()){pq2.push(pq.pop());}
iter(pq2,maxcolors-pq2.size());var cmap=new CMap();while(pq2.size()){cmap.push(pq2.pop());}
return cmap;}
return{quantize:quantize};})();var getColorContrast=function(color){if(!color){return null;}
var rgbExp=/^rgba?[\s+]?\(\s*(([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]))\s*,\s*([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\s*,\s*([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\s*,?(?:\s*([\d.]+))?\s*\)?\s*/im,rgb=color.match(rgbExp),r,g,b,yiq;if(rgb){r=parseInt(rgb[1],10);g=parseInt(rgb[2],10);b=parseInt(rgb[3],10);}else{return null;}
yiq=((r*299)+(g*587)+(b*114))/ 1000;return(yiq>=146)?'dark':'light';}
var colorThiefNew=new ColorThief();var processServerInfo=function(ot,sI,data,KA){var sIL=sI.length,sIFrag=document.createDocumentFragment(),serverInfo;for(var i=0;i<sIL;i++){if(ot.direct){serverInfo=data[sI[i]];}else if(ot.version===2){serverInfo=data.getElementsByTagName(sI[i].toUpperCase())[0].textContent;}else{var serverInfoV1=data.body.textContent.split(',');if(sI[i]==='currentlisteners'){serverInfo=serverInfoV1[0]}else if(sI[i]==='streamstatus'){serverInfo=serverInfoV1[1]}else if(sI[i]==='peaklisteners'){serverInfo=serverInfoV1[2]}else if(sI[i]==='maxlisteners'){serverInfo=serverInfoV1[3]}else if(sI[i]==='uniquelisteners'){serverInfo=serverInfoV1[4]}else if(sI[i]==='bitrate'){serverInfo=serverInfoV1[5]}else if(sI[i]==='songtitle'){serverInfo=serverInfoV1[6]}}
if(i===sIL-1){sIFrag.appendChild(document.createTextNode(serverInfo));}else{sIFrag.appendChild(document.createTextNode(serverInfo+' - '));}}
KA.appendChild(sIFrag);}
var processServerInfo2=function(ot,sI,data,KA){var sIL=sI.length,sIFrag2=document.createDocumentFragment(),serverInfo2;for(var i=0;i<sIL;i++){if(ot.direct){serverInfo2=data[sI[i]];}else if(ot.version===2){serverInfo2=data.getElementsByTagName(sI[i].toUpperCase())[0].textContent;}else{var serverInfoV1=data.body.textContent.split(',');if(sI[i]==='currentlisteners'){serverInfo2=serverInfoV1[0]}else if(sI[i]==='streamstatus'){serverInfo2=serverInfoV1[1]}else if(sI[i]==='peaklisteners'){serverInfo2=serverInfoV1[2]}else if(sI[i]==='maxlisteners'){serverInfo2=serverInfoV1[3]}else if(sI[i]==='uniquelisteners'){serverInfo2=serverInfoV1[4]}else if(sI[i]==='bitrate'){serverInfo2=serverInfoV1[5]}else if(sI[i]==='songtitle'){serverInfo2=serverInfoV1[6]}}
if(i===sIL-1){sIFrag2.appendChild(document.createTextNode('Bitrate: '+serverInfo2));}else{sIFrag2.appendChild(document.createTextNode(serverInfo2));}}
KA.appendChild(sIFrag2);}
var processServerInfo3=function(ot,sI,data,KA){var sIL=sI.length,sIFrag3=document.createDocumentFragment(),serverInfo3;for(var i=0;i<sIL;i++){if(ot.direct){serverInfo3=data[sI[i]];}else if(ot.version===2){serverInfo3=data.getElementsByTagName(sI[i].toUpperCase())[0].textContent;}else{var serverInfoV1=data.body.textContent.split(',');if(sI[i]==='currentlisteners'){serverInfo3=serverInfoV1[0]}else if(sI[i]==='streamstatus'){serverInfo3=serverInfoV1[1]}else if(sI[i]==='peaklisteners'){serverInfo3=serverInfoV1[2]}else if(sI[i]==='maxlisteners'){serverInfo3=serverInfoV1[3]}else if(sI[i]==='uniquelisteners'){serverInfo3=serverInfoV1[4]}else if(sI[i]==='bitrate'){serverInfo3=serverInfoV1[5]}else if(sI[i]==='songtitle'){serverInfo3=serverInfoV1[6]}}
if(i===sIL-1){sIFrag3.appendChild(document.createTextNode('Bitrate: '+serverInfo3+''));}else{sIFrag3.appendChild(document.createTextNode('Oyentes: '+serverInfo3+' | '));}}
KA.appendChild(sIFrag3);}
var XHR=function(op){var req;req=(window.XMLHttpRequest)?new XMLHttpRequest():new XDomainRequest();try{req.open('GET',op.url,true);if(op.arraybuffer){if(typeof req.responseType==='string'){req.responseType='arraybuffer';}else{if(op.error){op.error()}
return}}
req.timeout=op.timeout||3000;}catch(e){if(op.error){op.error()}
return}
req.onload=function(){if(req.readyState===4){if(req.status===200){var data=(op.arraybuffer)?req.response:req.responseText;op.load(data,req)}else{if(op.error){op.error()}}}}
if(op.error){req.onerror=op.error}
req.ontimeout=req.onerror;setTimeout(function(){req.send();},0);window.kastXHR=req}
var chaRe=function(strie){return strie.replace(/(\[.*?\]|\(.*?\))/g,'').replace(/[|&^'`;:$%@"#<>+,]/g,'')};function createHTMLDocument(str){var doc=document.implementation.createHTMLDocument('html');doc.documentElement.innerHTML=str;return doc}
var classL=document.documentElement.classList;Plugin.prototype={init:function(){var that=this,ot=that.opt;var docContainer=document.querySelector(ot.container);var clrs=ot.colors,primaryColor=(typeof clrs==='object')?'kast-primary-'+clrs.primary.replace(' ',''):'',accentColor=(typeof clrs==='object')?'kast-accent-'+clrs.accent.replace(' ',''):'',dynamicColors=(typeof clrs==='string')?'kast-colors-'+clrs:'',ultra=(that.mobile&&that.mobileUltra)?'kast-ultra':'',notFullBar=(!ot.statusBar||!ot.muteUnmute||!ot.minimizeMaximize)?'kast-not-full-statusbar':'',played=(ot.played)?' kast-played ':' kast-current ',container=(ot.container!=='body')?'kast-custom-container':'',thin=(docContainer.offsetWidth<380)?'kast-thin-container':'',dynamicTheme=(ot.theme==='dynamic')?'kast-light':'',statusBarHtml='',playedHtml='';if(ot.statusBar){var muteUnmuteHtml=(ot.muteUnmute)?'<i id="kast-volume" class="kast-mdi kast-mdi-volume-high"></i>':'',minMaxHtml=(ot.minimizeMaximize)?'<i id="kast-minmax" class="kast-mdi kast-mdi-chevron-down"></i>':'';statusBarHtml='<div id="kast-bar"><p class="kast-offline-status">'+ot.language.offlineText+'</p><p id="kast-server"></p>'+muteUnmuteHtml+minMaxHtml+'</div>';}
if(ot.played){playedHtml='<div id="kast-bottom" class="kast-clearfix"><p>'+ot.language.playedText+'</p><ul id="kast-playedlist" class="kast-clearfix"></ul></div>';}
var kastPlayClass=ot.continuous?'kast-paused kast-continuous ':'kast-stopped ';var html='';html+='<div id="kast" class="kast-recss kast-'+ot.theme+' kast-'+ot.ui+' '+primaryColor+' '+accentColor+' '+dynamicColors+' kast-'+ot.startTemplate+' kast-'+ot.position+' '+ultra+' '+notFullBar+played+' '+container+' '+dynamicTheme+' '+thin+'">'
html+='<div id="kast-wrapper">';html+=statusBarHtml;html+='<div id="kast-top" class="kast-default-art">';html+='<div class="kast-album-wrapper"><i class="kast-mdi kast-mdi-album"></i></div>';html+='<div id="kast-top-content" class="kast-top-content">';html+='<div id="kast-nowplaying"><p id="kast-np-title"></p><p id="kast-np-artist"></p></div>';html+='<div id="kast-linear"></div>';html+='</div>';html+='<div id="kast-play" class="'+kastPlayClass+'">';html+='<i class="kast-mdi kast-mdi-play"></i>';html+='<i class="kast-mdi kast-mdi-pause"></i>';html+='<i class="kast-mdi kast-mdi-stop"></i>';html+='</div></div>'+playedHtml+'</div></div>';docContainer.insertAdjacentHTML("beforeend",html);ot.onReady();if(ot.statusBar||ot.currentTrack||ot.currentArtist){this.stats(function(data){var sI=ot.serverInfo;if(sI&&ot.statusBar){var kastServer=document.getElementById('kast-server');if(typeof sI==='string'){kastServer.textContent=sI;}else{processServerInfo(ot,sI,data,kastServer)}}
that.stats(data);});}
if(ot.played){if(Array.isArray&&Array.isArray(ot.artwork)){that.played(false,true)}else{that.played()}}
var aU=ot.autoUpdate;if(aU==='all'){that.autoUpdate('all');}else if(aU){that.autoUpdate(true);}
document.getElementById('kast-play').onclick=function(){if(this.className.indexOf('playing')===-1){that.play(!ot.continuous)}else{ot.continuous?that.pause():that.stop()}};if(ot.statusBar){if(ot.muteUnmute){document.getElementById('kast-volume').onclick=function(){if(this.className.indexOf('high')!==-1){that.mute()}else{that.unmute()}};}
if(ot.minimizeMaximize){document.getElementById('kast-minmax').onclick=function(){if(kast.className.indexOf('minimized')!==-1){that.maximize()}else{that.minimize()}};}}
ot.autoPlay&&that.play();ot.startMuted&&that.mute();return this;},play:function(reload){var k=document.getElementById('kast'),kP=document.getElementById('kast-play');if(classL){var kPC=kP.classList;kPC.remove('kast-paused')
kPC.remove('kast-stopped')
kPC.add('kast-playing')}else{$(kP).removeClass('kast-paused kast-stopped').addClass('kast-playing')}
var wasOffline=(this.opt.offlineCheck&&k.getAttribute('data-offline')==='false');if(reload||wasOffline){this.audio.load();wasOffline&&k.removeAttribute('data-offline')}
this.audio.play();this.opt.onPlay(this.audio)
return this;},pause:function(){var kP=document.getElementById('kast-play');if(classL){var kPC=kP.classList;kPC.remove('kast-playing')
kPC.remove('kast-stopped')
kPC.add('kast-paused')
kPC.add('kast-continuous')}else{$(kP).removeClass('kast-playing kast-stopped').addClass('kast-paused kast-continuous')}
this.audio.pause();this.opt.onPause(this.audio)
return this;},stop:function(){var kP=document.getElementById('kast-play');if(classL){var kPC=kP.classList;kPC.remove('kast-playing')
kPC.remove('kast-paused')
kPC.remove('kast-continuous')
kPC.add('kast-stopped')}else{$(kP).removeClass('kast-playing kast-paused kast-continuous').addClass('kast-stopped')}
this.audio.pause();this.opt.onStop(this.audio)
return this;},mute:function(){document.getElementById('kast-volume').className='kast-mdi kast-mdi-volume-off';this.audio.muted=true;this.opt.onMute(this.audio)
return this},unmute:function(){document.getElementById('kast-volume').className='kast-mdi kast-mdi-volume-high';this.audio.muted=false;this.opt.onUnmute(this.audio)
return this},minimize:function(){var k=document.getElementById('kast');if(classL){var kC=k.classList;kC.remove('kast-maximized')
kC.add('kast-minimized')}else{$(k).removeClass('kast-maximized').addClass('kast-minimized');}
this.opt.onMinimize()
return this;},maximize:function(){var k=document.getElementById('kast');if(classL){var kC=k.classList;kC.remove('kast-minimized')
kC.add('kast-maximized')}else{$(k).removeClass('kast-minimized').addClass('kast-maximized');}
this.opt.onMaximize()
return this;},stats:function(callback){var that=this,ot=that.opt;var kast=document.getElementById('kast'),kastTitle=document.getElementById('kast-np-title'),kastArtist=document.getElementById('kast-np-artist'),kastTop=document.getElementById('kast-top'),kastBar=document.getElementById('kast-bar'),kastTopC=document.getElementById('kast-top-content'),kastPlay=document.getElementById('kast-play');var processStats=function(data){var songTitle,currentTrack,currentArtist;var unTrack=ot.language.unknownTrackText,unArtist=ot.language.unknownArtistText;try{songTitle=(ot.direct?data.songtitle:(ot.version===2)?data.getElementsByTagName('SONGTITLE')[0].textContent:data.body.textContent.split(',')[6])||unArtist+' - '+unTrack;}catch(e){songTitle=unArtist+' - '+unTrack;}
if(typeof ot.currentTrack==='string'){currentTrack=ot.currentTrack;}else{currentTrack=songTitle.split(' - ')[1]||songTitle||unTrack;}
if(typeof ot.currentArtist==='string'){currentArtist=ot.currentArtist;}else{currentArtist=songTitle.split(' - ')[0]||unArtist;}
if(ot.currentTrack){kastTitle.textContent=currentTrack;}
if(ot.currentArtist){kastArtist.textContent=currentArtist;}
if(ot.artwork){that.artwork(currentArtist,currentTrack,function(imgAr){if(!imgAr){if(classL){var kC=kast.classList,kPC=kastPlay.classList;kPC.remove('kast-accent-light')
kPC.remove('kast-accent-dark')
if(ot.theme==='dark'){kC.remove('kast-light')
kC.add('kast-dark')}else{kC.remove('kast-dark')
kC.add('kast-light')}}else{$(kastPlay).removeClass('kast-accent-light kast-accent-dark');if(ot.theme==='dark'){$(kast).removeClass('kast-light').addClass('kast-dark');}else{$(kast).removeClass('kast-dark').addClass('kast-light');}}
kastTop.className='kast-default-art';if(ot.statusBar){kastBar.removeAttribute('class')}
kastPlay.removeAttribute('style')
kastTop.removeAttribute('style');kastTopC.removeAttribute('style');kastTopC.className='kast-top-content';}else{var imgURL=imgAr[0],imgLite=imgAr[1]||imgURL;kastTop.style.backgroundImage='url('+imgURL+')';kastTop.removeAttribute('class')
ot.onCurrentArtwork(imgURL)
if((ot.theme==='dynamic'||ot.colors==='dynamic')&&window.Blob){XHR({url:imgLite,arraybuffer:true,load:function(data,req){window.URL=window.URL||window.webkitURL;var img=document.createElement('img'),contentType=req.getResponseHeader('content-type'),uData=new Uint8Array(data),blob=new Blob([uData],{type:contentType});img.src=window.URL.createObjectURL(blob);img.onload=function(){var color=colorThiefNew.getPalette(img,5),primaryBG='rgb('+color[0]+')',accentBG='rgb('+color[1]+')',primaryContrast=getColorContrast(primaryBG)||'light',primaryCC='kast-primary-'+primaryContrast,accentContrast=getColorContrast(accentBG)||'dark',accentCC='kast-accent-'+accentContrast;if(ot.colors==='dynamic'){var kastPlayClass=ot.continuous?'kast-paused ':'kast-stopped ';var kPC=kastPlay.className;if(kPC.indexOf('playing')!==-1){kastPlay.className='kast-playing '+accentCC}else{kastPlay.className=kastPlayClass+accentCC}
if(ot.continuous){kastPlay.className+=' kast-continuous ';}
kastTopC.className='kast-top-content '+primaryCC;if(ot.statusBar){kastBar.className=primaryCC;}
kastPlay.style.backgroundColor=accentBG;if(ot.ui==='colored'){kastTopC.style.backgroundColor=primaryBG;}
ot.onDynamicColors(primaryBG,accentBG)
ot.onDynamicColorsContrast(primaryContrast,accentContrast)}
if(ot.theme==='dynamic'){if(primaryContrast==='light'){if(classL){var kC=kast.classList;kC.remove('kast-dark')
kC.add('kast-light')}else{$(kast).removeClass('kast-dark').addClass('kast-light')}
ot.onDynamicTheme('light')}else{if(classL){var kC=kast.classList;kC.remove('kast-light')
kC.add('kast-dark')}else{$(kast).removeClass('kast-light').addClass('kast-dark')}
ot.onDynamicTheme('dark')}}
window.URL.revokeObjectURL(img.src)
img=null}}})}}})}
ot.onCurrentInfo(currentTrack,currentArtist)};if(typeof callback==='object'){processStats(callback)}else{var ajaxStats=function(hostCORSproxy,showError){var url=hostCORSproxy+ot.statsPath+'?sid='+ot.sid,urlParm=(ot.version===1)?'#':'?_=';if(ot.version===1){url=hostCORSproxy+'7.html';}
XHR({url:url+urlParm+Math.random(),timeout:8000,load:function(data){var dataDOM=(ot.version===1)?createHTMLDocument(data):new DOMParser().parseFromString(data,'text/xml');if(typeof callback==='function'){callback(dataDOM);}else{processStats(dataDOM)}},error:function(){if(showError){var isOffline=kast.hasAttribute('data-offline'),kastNT=document.getElementById('kast-np-title');if(ot.offlineCheck&&ot.autoUpdate&&!isOffline){if(classL){kast.classList.add('kast-offline');}else{$(kast).addClass('kast-offline');}
kast.setAttribute('data-offline','true')
ot.onOffline();}
if(!kastNT.hasChildNodes()){processStats('error')}}else{ajaxStats(that.hostCORS[ot.betaProxies?3:1],true)}}})}
var directStats=function(){$.ajax({url:that.host+ot.statsPath+'?sid='+ot.sid+'&json=1&_='+Math.random(),dataType:'jsonp',timeout:8000,success:function(data){if(typeof callback==='function'){callback(data);}else{processStats(data)}},error:function(){var isOffline=kast.hasAttribute('data-offline'),kastNT=document.getElementById('kast-np-title');if(ot.offlineCheck&&ot.autoUpdate&&!isOffline){if(classL){kast.classList.add('kast-offline');}else{$(kast).addClass('kast-offline');}
kast.setAttribute('data-offline','true')
ot.onOffline();}
if(!kastNT.hasChildNodes()){processStats('error')}}})}
if(ot.direct){directStats()}else{ajaxStats(that.hostCORS[ot.betaProxies?2:0],false)}}
return this},played:function(callback,woArtwork){var that=this,ot=that.opt;var kastPL=document.getElementById('kast-playedlist');var processPlayed=function(data){while(kastPL.firstChild){kastPL.removeChild(kastPL.firstChild);}
var song,songL,songsFrag=document.createDocumentFragment(),unTrack=ot.language.unknownTrackText,unArtist=ot.language.unknownArtistText;try{song=ot.direct?data:(ot.version===2)?data.getElementsByTagName('SONG'):data.getElementsByTagName('table')[2].getElementsByTagName('tr');songL=song.length;}catch(e){songL=3;}
var processPL=function(j,song,songL,songsFrag){var playedTrack,playedArtist,title;try{title=(ot.direct?song[j].title:(ot.version===2)?song[j].getElementsByTagName('TITLE')[0].textContent:song[j].getElementsByTagName('td')[1].textContent)||unArtist+' - '+unTrack;}catch(e){title=unArtist+' - '+unTrack;}
if(ot.playedTracks){playedTrack=title.split(' - ')[1]||title||unTrack;}
if(ot.playedArtists){playedArtist=title.split(' - ')[0]||unArtist;}
var li=document.createElement('li'),divA=document.createElement('div'),i=document.createElement('i'),divI=document.createElement('div'),pTitle=document.createElement('p'),pArtist=document.createElement('p');divA.className='kast-p-art';i.className='kast-mdi kast-mdi-album';divI.className='kast-p-info';pTitle.className='kast-p-title';pTitle.textContent=playedTrack;pArtist.className='kast-p-artist';pArtist.textContent=playedArtist;li.appendChild(divA);li.appendChild(divI);divA.appendChild(i);divI.appendChild(pTitle);divI.appendChild(pArtist);if(ot.artwork&&!woArtwork){that.artwork(playedArtist,playedTrack,function(imgAr){if(imgAr){divA.style.backgroundImage='url('+imgAr[1]+')';ot.onPlayedArtworks(imgAr[1])}else{divA.className='kast-p-art kast-p-default-art';}})}else{divA.className='kast-p-art kast-p-default-art';}
ot.onPlayedInfo(playedTrack,playedArtist)
songsFrag.appendChild(li)}
var jV=(ot.version===2)?1:2;for(var j=jV;j<songL;j++){processPL(j,song,songL,songsFrag)}
kastPL.appendChild(songsFrag);},ajaxPlayed=function(hostCORSproxy,showError){var url=hostCORSproxy+ot.playedPath+'?sid='+ot.sid+'&type=xml',urlParm=(ot.version===1)?'#':'&_=';if(ot.version===1){url=hostCORSproxy+ot.playedPath+'.html';}
XHR({url:url+urlParm+Math.random(),timeout:8000,load:function(data){var dataDOM=(ot.version===1)?createHTMLDocument(data):new DOMParser().parseFromString(data,'text/xml');if(callback){callback(dataDOM)}else{processPlayed(dataDOM)}},error:function(data){if(showError){if(!kastPL.hasChildNodes()){processPlayed('error')}}else{ajaxPlayed(that.hostCORS[ot.betaProxies?3:1],true)}}})},directPlayed=function(){$.ajax({url:that.host+ot.playedPath+'?sid='+ot.sid+'&type=json',timeout:8000,dataType:'jsonp',success:function(data){if(callback){callback(data)}else{processPlayed(data)}},error:function(){if(!kastPL.hasChildNodes()){processPlayed('error')}}})}
if(ot.direct){directPlayed()}else{ajaxPlayed(that.hostCORS[ot.betaProxies?2:0],false)}
return this},autoUpdate:function(uKey){var that=this,ot=that.opt;var kast=document.getElementById('kast'),kastServer=document.getElementById('kast-server'),kastPlay=document.getElementById('kast-play'),kastC;if(classL){kastC=kast.classList;}
if(!uKey){clearInterval(kast.getAttribute('data-interval'))
kast.removeAttribute('data-interval')
return}
var checker=function(){that.stats(function(data){var isPlaying=(kastPlay.className.indexOf('playing')!==-1);if(ot.offlineCheck){var SS=ot.direct?data.streamstatus:(ot.version===2)?data.getElementsByTagName('STREAMSTATUS')[0].textContent:data.body.textContent.split(',')[1];var isOffline=kast.hasAttribute('data-offline');if(!data||SS!=1){if(!isOffline){if(classL){kastC.add('kast-offline')}else{$(kast).addClass('kast-offline')}
kast.setAttribute('data-offline','true');ot.onOffline();}}else{if(isOffline){if(classL){kastC.remove('kast-offline')}else{$(kast).removeClass('kast-offline')}
kast.setAttribute('data-offline','false');ot.onOnline()}}}
isPlaying&&that.play();if(uKey==='all'){var sI=ot.serverInfo,sB=ot.statusBar;if(typeof sI!=='string'&&sB){kastServer.textContent='';processServerInfo(ot,sI,data,kastServer)}}
var customTA=(typeof ot.currentTrack==='string'&&typeof ot.currentArtist==='string');if(customTA&&!ot.played){ot.onUpdate(data)
ot.onUpdateAll(data)
return}
var streamSTitle=ot.direct?data.songtitle:(ot.version===2)?data.getElementsByTagName('SONGTITLE')[0].textContent:data.body.textContent.split(',')[6],currentSTitle=kast.getAttribute('data-current');if(!currentSTitle){return kast.setAttribute('data-current',streamSTitle);}
if(currentSTitle!==streamSTitle){if(!customTA){that.stats(data);}
if(ot.played){var isArtArr=(Array.isArray&&Array.isArray(ot.artwork));if(isArtArr){that.played(false,true)}else{that.played()}}
kast.setAttribute('data-current',streamSTitle);ot.onUpdate(data)}
ot.onUpdateAll(data)})},setTimer=function(fn,time){if(!kast.hasAttribute('data-interval')){var setInterID=setInterval(fn,time);kast.setAttribute('data-interval',setInterID)}},timeMS=8000;if(that.mobile){timeMS=(that.mobileMedium)?16000:12000;}
setTimer(checker,timeMS)
return this},artwork:function(artist,track,callback){var that=this,ot=this.opt;if(Array.isArray&&Array.isArray(ot.artwork)){return callback(ot.artwork)}
if(artist===ot.language.unknownArtistText){return callback(null)}
var artistC=chaRe(artist),trackC=chaRe(track),processArtworkX=function(data){var imgAr=null;if(data.tracks&&data.tracks.items[0]){var imagesArrayT=data.tracks.items[0].album.images||'',imgLarge,imgSmall=imagesArrayT[2].url||'';if(that.mobileMedium){imgLarge=imagesArrayT[1].url||'';}else{imgLarge=imagesArrayT[0].url||'';}
if(imgLarge&&imgSmall){imgAr=[imgLarge,imgSmall];}}else if(data.artists&&data.artists.items[0]&&data.artists.items[0].images[0]){var imagesArrayA=data.artists.items[0].images||'',imgLarge=null,imgSmall=null;if(data.artists.items[0].images.length===4){if(that.mobileMedium){imgLarge=imagesArrayA[2].url||'';}else{imgLarge=imagesArrayA[1].url||'';}
imgSmall=imagesArrayA[3].url||'';}else{if(that.mobileMedium){imgLarge=imagesArrayA[1].url||'';}else{imgLarge=imagesArrayA[0].url||'';}
imgSmall=imagesArrayA[2].url||'';}
if(imgLarge&&imgSmall){imgAr=[imgLarge,imgSmall];}}
return imgAr},ajaxArtwork=function(artistN,trackN,noLuck){var spotifyTrackAPI='https://api.spotify.com/v1/search?q=artist:'+artistN+'%20track:'+trackN+'&limit=1&type=track',spotifyArtistAPI='https://api.spotify.com/v1/search?q=artist:'+artistN+'&limit=1&type=artist',spotifyAPI=noLuck?spotifyArtistAPI:spotifyTrackAPI;XHR({url:spotifyAPI,load:function(data){var dataJSON=JSON.parse(data);var imgAr=processArtworkX(dataJSON);if(imgAr){callback(imgAr)}else{if(noLuck){callback(null)}else{ajaxArtwork(artistN,trackN,true)}}},error:function(){callback(null)}})},iW=ot.irrelevantWords;if(iW){var iWL=iW.length;for(var i=0;i<iWL;i++){artistC=artistC.replace(iW[i],'')
trackC=trackC.replace(iW[i],'')}
ajaxArtwork(artistC,trackC)}else{ajaxArtwork(artistC,trackC)}
return this},destroy:function(){window.kastXHR&&window.kastXHR.abort();this.autoUpdate(false);this.audio.pause();$.data(document.body,'plugin_kast',null);var k=document.getElementById('kast');k&&k.parentNode.removeChild(k)
return this}}
$.kast=function(options,keys){var dB=document.body;if(!$.data(dB,'plugin_kast')){if(options==='destroy'){return}
$.data(dB,'plugin_kast',new Plugin(this,options));}else if(typeof Plugin.prototype[options]==='function'){$.data(dB,'plugin_kast')[options](keys);}}})(jQuery,window,document);