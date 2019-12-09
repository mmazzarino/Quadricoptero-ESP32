const char MAIN_pageA[] PROGMEM = R"=====(<html>
 <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0">
    
    <style>
    body {
      overflow  : hidden;
      padding   : 0;
      margin    : 0;
      background-color: #BBB;
    }
    #info {
      position  : absolute;
      top   : 0px;
      width   : 100%;
      padding   : 5px;
      text-align  : center;
    }
    #info a {
      color   : #66F;
      text-decoration : none;
    }
    #info a:hover {
      text-decoration : underline;
    }
    #container {
      width   : 100%;
      height    : 100%;
      overflow  : hidden;
      padding   : 0;
      margin    : 0;
      -webkit-user-select : none;
      -moz-user-select  : none;
    }
    </style>
  </head>
  <body>
  )=====";
   
    
    
    
const char MAIN_pageB[] PROGMEM = R"=====(<div id="container"></div>
    <div id="info">
      <b>JOYSTICK VIRTUAL</b><br><br>
      
      Toca la pantalla para moverlo
      -
      También se puede utilizar el ratón
      <br>
      <span id="result"></span>
    </div> 
    <script>
        var VirtualJoystick = function(opts)
            {
              opts      = opts      || {};
              this._container   = opts.container  || document.body;
              this._strokeStyle = opts.strokeStyle  || 'cyan';
              this._stickEl   = opts.stickElement || this._buildJoystickStick();
              this._baseEl    = opts.baseElement  || this._buildJoystickBase();
              this._mouseSupport  = opts.mouseSupport !== undefined ? opts.mouseSupport : false;
              this._stationaryBase  = opts.stationaryBase || false;
              this._baseX   = this._stickX = opts.baseX || screen.width/2
              this._baseY   = this._stickY = opts.baseY || screen.height/2
              this._limitStickTravel = opts.limitStickTravel || true;
                if (screen.width >= screen.height){
                    this._stickRadius = opts.stickRadius !== undefined ? opts.stickRadius : screen.height*0.35;
                }
                else {
                    this._stickRadius = opts.stickRadius !== undefined ? opts.stickRadius : screen.width*0.35;
                };
              this._useCssTransform = opts.useCssTransform !== undefined ? opts.useCssTransform : false
            
              this._container.style.position  = "relative"
            
              this._container.appendChild(this._baseEl)
              this._baseEl.style.position = "absolute"
              this._baseEl.style.display  = "none"
              this._container.appendChild(this._stickEl)
              this._stickEl.style.position  = "absolute"
              this._stickEl.style.display = "none"
            
              this._pressed = false;
              this._touchIdx  = null;
              
              if(this._stationaryBase === true){
                this._baseEl.style.display  = "";
                this._baseEl.style.left   = (this._baseX - this._baseEl.width /2)+"px";
                this._baseEl.style.top    = (this._baseY - this._baseEl.height/2)+"px";
              }
                
              this._transform = this._useCssTransform ? this._getTransformProperty() : false;
              this._has3d = this._check3D();
              
              var __bind  = function(fn, me){ return function(){ return fn.apply(me, arguments); }; };
              this._$onTouchStart = __bind(this._onTouchStart , this);
              this._$onTouchEnd = __bind(this._onTouchEnd , this);
              this._$onTouchMove  = __bind(this._onTouchMove  , this);
              this._container.addEventListener( 'touchstart'  , this._$onTouchStart , false );
              this._container.addEventListener( 'touchend'  , this._$onTouchEnd , false );
              this._container.addEventListener( 'touchmove' , this._$onTouchMove  , false );
              if( this._mouseSupport ){
                this._$onMouseDown  = __bind(this._onMouseDown  , this);
                this._$onMouseUp  = __bind(this._onMouseUp  , this);
                this._$onMouseMove  = __bind(this._onMouseMove  , this);
                this._container.addEventListener( 'mousedown' , this._$onMouseDown  , false );
                this._container.addEventListener( 'mouseup' , this._$onMouseUp  , false );
                this._container.addEventListener( 'mousemove' , this._$onMouseMove  , false );
              }
            }
            )=====";
            
            const char MAIN_pageC[] PROGMEM = R"=====(
            VirtualJoystick.prototype.destroy = function()
            {
              this._container.removeChild(this._baseEl);
              this._container.removeChild(this._stickEl);
            
              this._container.removeEventListener( 'touchstart' , this._$onTouchStart , false );
              this._container.removeEventListener( 'touchend'   , this._$onTouchEnd , false );
              this._container.removeEventListener( 'touchmove'  , this._$onTouchMove  , false );
              if( this._mouseSupport ){
                this._container.removeEventListener( 'mouseup'    , this._$onMouseUp  , false );
                this._container.removeEventListener( 'mousedown'  , this._$onMouseDown  , false );
                this._container.removeEventListener( 'mousemove'  , this._$onMouseMove  , false );
              }
            }
            )=====";

            const char MAIN_pageD[] PROGMEM = R"=====(
            VirtualJoystick.touchScreenAvailable  = function()
            {
              return 'createTouch' in document ? true : false;
            }
            
            ;(function(destObj){
              destObj.addEventListener  = function(event, fct){
                if(this._events === undefined)  this._events  = {};
                this._events[event] = this._events[event] || [];
                this._events[event].push(fct);
                return fct;
              };
              destObj.removeEventListener = function(event, fct){
                if(this._events === undefined)  this._events  = {};
                if( event in this._events === false  )  return;
                this._events[event].splice(this._events[event].indexOf(fct), 1);
              };
              )=====";

              const char MAIN_pageE[] PROGMEM = R"=====(
              destObj.dispatchEvent   = function(event /* , args... */){
                if(this._events === undefined)  this._events  = {};
                if( this._events[event] === undefined ) return;
                var tmpArray  = this._events[event].slice(); 
                for(var i = 0; i < tmpArray.length; i++){
                  var result  = tmpArray[i].apply(this, Array.prototype.slice.call(arguments, 1))
                  if( result !== undefined )  return result;
                }
                return undefined
              };
            })(VirtualJoystick.prototype);
            )=====";

            const char MAIN_pageF[] PROGMEM = R"=====(
            VirtualJoystick.prototype.deltaX  = function(){ return this._stickX - this._baseX;  }
            VirtualJoystick.prototype.deltaY  = function(){ return this._stickY - this._baseY;  }
            
            VirtualJoystick.prototype.up  = function(){
              if( this._pressed === false ) return false;
              var deltaX  = this.deltaX();
              var deltaY  = this.deltaY();
              if( deltaY >= 0 )       return false;
              if( Math.abs(deltaX) > 2*Math.abs(deltaY) ) return false;
              return true;
            }
            VirtualJoystick.prototype.down  = function(){
              if( this._pressed === false ) return false;
              var deltaX  = this.deltaX();
              var deltaY  = this.deltaY();
              if( deltaY <= 0 )       return false;
              if( Math.abs(deltaX) > 2*Math.abs(deltaY) ) return false;
              return true;  
            }
            )=====";

            const char MAIN_pageG[] PROGMEM = R"=====(
            VirtualJoystick.prototype.right = function(){
              if( this._pressed === false ) return false;
              var deltaX  = this.deltaX();
              var deltaY  = this.deltaY();
              if( deltaX <= 0 )       return false;
              if( Math.abs(deltaY) > 2*Math.abs(deltaX) ) return false;
              return true;  
            }
            VirtualJoystick.prototype.left  = function(){
              if( this._pressed === false ) return false;
              var deltaX  = this.deltaX();
              var deltaY  = this.deltaY();
              if( deltaX >= 0 )       return false;
              if( Math.abs(deltaY) > 2*Math.abs(deltaX) ) return false;
              return true;  
            }

            
            VirtualJoystick.prototype._onUp = function()
            {
              this._pressed = false; 
              this._stickEl.style.display = "none";
              
              if(this._stationaryBase == true){ 
                this._stickX = this._baseX;
          this._stickY = this._baseY;         
              }             
              if(this._stationaryBase == false){  
                this._baseEl.style.display  = "none";
          this._stickX = this._baseX = 0;
          this._stickY = this._baseY = 0;           
              }
            }
            )=====";

            const char MAIN_pageH[] PROGMEM = R"=====(
            VirtualJoystick.prototype._onDown = function(x, y)
            {
              this._pressed = true; 
              if(this._stationaryBase == false){
                this._baseX = x;
                this._baseY = y;
                this._baseEl.style.display  = "";
                this._move(this._baseEl.style, (this._baseX - this._baseEl.width /2), (this._baseY - this._baseEl.height/2));
              }
              
              this._stickX  = x;
              this._stickY  = y;
              
              if(this._limitStickTravel === true){
                var deltaX  = this.deltaX();
                var deltaY  = this.deltaY();
                var stickDistance = Math.sqrt( (deltaX * deltaX) + (deltaY * deltaY) );
                if(stickDistance > this._stickRadius){
                  var stickNormalizedX = deltaX / stickDistance;
                  var stickNormalizedY = deltaY / stickDistance;
                  
                  this._stickX = stickNormalizedX * this._stickRadius + this._baseX;
                  this._stickY = stickNormalizedY * this._stickRadius + this._baseY;
                }   
              }
              
              this._stickEl.style.display = "";
              this._move(this._stickEl.style, (this._stickX - this._stickEl.width /2), (this._stickY - this._stickEl.height/2));  
            }
            )=====";


            const char MAIN_pageI[] PROGMEM = R"=====(
            VirtualJoystick.prototype._onMove = function(x, y)
            {
              if( this._pressed === true ){
                this._stickX  = x;
                this._stickY  = y;
                
                if(this._limitStickTravel === true){
                  var deltaX  = this.deltaX();
                  var deltaY  = this.deltaY();
                  var stickDistance = Math.sqrt( (deltaX * deltaX) + (deltaY * deltaY) );
                  if(stickDistance > this._stickRadius){
                    var stickNormalizedX = deltaX / stickDistance;
                    var stickNormalizedY = deltaY / stickDistance;
                  
                    this._stickX = stickNormalizedX * this._stickRadius + this._baseX;
                    this._stickY = stickNormalizedY * this._stickRadius + this._baseY;
                  }     
                }
                
                      this._move(this._stickEl.style, (this._stickX - this._stickEl.width /2), (this._stickY - this._stickEl.height/2));  
              } 
            }
            )=====";
            

            const char MAIN_pageJ[] PROGMEM = R"=====(
            VirtualJoystick.prototype._onMouseUp  = function(event)
            {
              return this._onUp();
            }
            
            VirtualJoystick.prototype._onMouseDown  = function(event)
            {
              event.preventDefault();
              var x = event.clientX;
              var y = event.clientY;
              return this._onDown(x, y);
            }
            
            VirtualJoystick.prototype._onMouseMove  = function(event)
            {
              var x = event.clientX;
              var y = event.clientY;
              return this._onMove(x, y);
            }
            

            
            VirtualJoystick.prototype._onTouchStart = function(event)
            {
   
              if( this._touchIdx !== null ) return;
            
    
              var isValid = this.dispatchEvent('touchStartValidation', event);
              if( isValid === false ) return;
              
   
              this.dispatchEvent('touchStart', event);
            
              event.preventDefault();
    
              var touch = event.changedTouches[0];
  
              this._touchIdx  = touch.identifier;
            

              var x   = touch.pageX;
              var y   = touch.pageY;
              return this._onDown(x, y)
            }
            )=====";

            const char MAIN_pageK[] PROGMEM = R"=====(
            VirtualJoystick.prototype._onTouchEnd = function(event)
            {

              if( this._touchIdx === null ) return;
            

              this.dispatchEvent('touchEnd', event);

              var touchList = event.changedTouches;
              for(var i = 0; i < touchList.length && touchList[i].identifier !== this._touchIdx; i++);
 
              if( i === touchList.length) return;
            

              this._touchIdx  = null;

            event.preventDefault();
            
              return this._onUp()
            }
            
            VirtualJoystick.prototype._onTouchMove  = function(event)
            {

              if( this._touchIdx === null ) return;
            

              var touchList = event.changedTouches;
              for(var i = 0; i < touchList.length && touchList[i].identifier !== this._touchIdx; i++ );
      
              if( i === touchList.length) return;
              var touch = touchList[i];
            
              event.preventDefault();
            
              var x   = touch.pageX;
              var y   = touch.pageY;
              return this._onMove(x, y)
            }
            )=====";
            
            
 
            
            const char MAIN_pageL[] PROGMEM = R"=====(
            VirtualJoystick.prototype._buildJoystickBase  = function()
            {
                var canvas  = document.createElement( 'canvas' );
                if (screen.width >= screen.height){
                    canvas.width = screen.height*0.7;
                }
                else {
                    canvas.width  = screen.width*0.7;
                };
             
                canvas.height = canvas.width;
             
                var ctx = canvas.getContext('2d');
                ctx.beginPath();
                ctx.fillStyle = "#AAA";
                ctx.arc(canvas.width/2, canvas.width/2,canvas.width/2,0,Math.PI*2,true);
                ctx.closePath();
                ctx.fill();
             
                ctx.beginPath(); 
                ctx.strokeStyle = this._strokeStyle; 
                ctx.lineWidth = 6;
                ctx.arc( canvas.width/2, canvas.width/2, 40, 0, Math.PI*2, true); 
                ctx.stroke(); 
             
                ctx.beginPath(); 
                ctx.strokeStyle = "#69C";
                ctx.lineWidth = 4;
                ctx.arc( canvas.width/2, canvas.width/2, canvas.width/2-2, 0, Math.PI*2, true);
                ctx.stroke();
             
                ctx.beginPath();
                ctx.lineWidth = 3;
                ctx.moveTo(canvas.width/2,0);
                ctx.lineTo(canvas.width/2,canvas.width/2);
                ctx.stroke();
             
                ctx.lineWidth = 1;
                ctx.moveTo(canvas.width/2,0);
                ctx.lineTo(canvas.width/2,canvas.width);
                ctx.moveTo(0,canvas.width/2);
                ctx.lineTo(canvas.width,canvas.width/2);
                ctx.stroke();
             
                return canvas;  
            }
            )=====";


            const char MAIN_pageM[] PROGMEM = R"=====(
            VirtualJoystick.prototype._buildJoystickStick = function()
            {
              var canvas  = document.createElement( 'canvas' );
              canvas.width  = 86;
              canvas.height = 86;
              var ctx   = canvas.getContext('2d');
              ctx.beginPath(); 
              ctx.strokeStyle = this._strokeStyle; 
              ctx.lineWidth = 6; 
              ctx.arc( canvas.width/2, canvas.width/2, 40, 0, Math.PI*2, true); 
              ctx.stroke();
              return canvas;
            }
            

            
            VirtualJoystick.prototype._move = function(style, x, y)
            {
              if (this._transform) {
                if (this._has3d) {
                  style[this._transform] = 'translate3d(' + x + 'px,' + y + 'px, 0)';
                } else {
                  style[this._transform] = 'translate(' + x + 'px,' + y + 'px)';
                }
              } else {
                style.left = x + 'px';
                style.top = y + 'px';
              }
            }
            
            VirtualJoystick.prototype._getTransformProperty = function() 
            {
              var styles = [
                'webkitTransform',
                'MozTransform',
                'msTransform',
                'OTransform',
                'transform'
              ];
              )=====";


            const char MAIN_pageN[] PROGMEM = R"=====(
              var el = document.createElement('p');
              var style;
            
              for (var i = 0; i < styles.length; i++) {
                style = styles[i];
                if (null != el.style[style]) {
                  return style;
                }
              }         
            }
              
            VirtualJoystick.prototype._check3D = function() 
            {        
              var prop = this._getTransformProperty();
              if (!prop || !window.getComputedStyle) return module.exports = false;
            
              var map = {
                webkitTransform: '-webkit-transform',
                OTransform: '-o-transform',
                msTransform: '-ms-transform',
                MozTransform: '-moz-transform',
                transform: 'transform'
              };
            

              var el = document.createElement('div');
              el.style[prop] = 'translate3d(1px,1px,1px)';
              document.body.insertBefore(el, null);
              var val = getComputedStyle(el).getPropertyValue(map[prop]);
              document.body.removeChild(el);
              var exports = null != val && val.length && 'none' != val;
              return exports;
            }
    </script>
    <script>
    )=====";

    const char MAIN_pageO[] PROGMEM = R"=====(
      console.log("touchscreen is", VirtualJoystick.touchScreenAvailable() ? "available" : "not available");
  
      var joystick  = new VirtualJoystick({
        container : document.getElementById('container'),
        mouseSupport  : true,
      });
      joystick.addEventListener('touchStart', function(){
        console.log('down')
      })
      joystick.addEventListener('touchEnd', function(){
        console.log('up')
      })
      
      var deltaXprevia = 0;
      var deltaYprevia = 0;
      var deltaX_corregida = 0;
      var deltaY_corregida = 0;
      
      setInterval(function(){
                if (screen.width >= screen.height){
                    var stickRadius = screen.height*0.35;
                }
                else {
                    var stickRadius = screen.width*0.35;
                };
            
                var deltaX_corregida=(joystick.deltaX()/stickRadius*255).toFixed();
                var deltaY_corregida=(-joystick.deltaY()/stickRadius*255).toFixed();
                var stick = Math.sqrt((deltaX_corregida*deltaX_corregida)+(deltaY_corregida*deltaY_corregida)).toFixed();
                if (deltaX_corregida >= 0 & deltaY_corregida >= 0){
                    var angulo = (Math.atan(deltaY_corregida/deltaX_corregida)/(2*Math.PI)*360).toFixed()
                }
                if (deltaX_corregida < 0) {
                    var angulo = ((Math.atan(deltaY_corregida/deltaX_corregida)/(2*Math.PI)*360)+180).toFixed()
                }
                if (deltaX_corregida >= 0 & deltaY_corregida < 0){
                    var angulo = ((Math.atan(deltaY_corregida/deltaX_corregida)/(2*Math.PI)*360)+360).toFixed()
                }
            
                var outputEl = document.getElementById('result');
                outputEl.innerHTML  = '<b>RESULTADO: </b>'
                + '<b> dx:</b>'+deltaX_corregida
                + '<b> dy:</b>'+deltaY_corregida
                + '<b> Vector (stick):</b>'+stick
                + '<br><b> Ángulo:</b>'+angulo
                + '<b> Orientación:</b>'
                + (joystick.right() ? ' Derecha'   : '')
                + (joystick.up()    ? ' Arriba'    : '')
                + (joystick.left()  ? ' Izquierda' : '')
                + (joystick.down()  ? ' Abajo'     : '')
                
                if (deltaX_corregida != deltaXprevia || deltaY_corregida != deltaYprevia ){
            var req = new XMLHttpRequest();
            req.open('GET', '/stick?dx=' + deltaX_corregida + '&dy=' + deltaY_corregida);
            req.send(null);
            deltaXprevia = deltaX_corregida;
            deltaYprevia = deltaY_corregida;      
            }
      }, 1/30 * 1000);
  
    </script>
  </body>
</html>
)=====";
