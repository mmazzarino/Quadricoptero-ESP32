/*PROGMEM = T"=====(<!DOCTYPE HTML>
<html>
  <head>
    <title>Joy</title>
    
    <style type="text/css">
        body{
          border: 5px solid #1C1C1C;}

        #titulo{
          text-align: center;}
 
        #joy1{
          margin-left: 25%;
          float: left; 
          width: 30%;}
    
        #joy2{
          margin-left: 65%;}  
		  
	
        
    </style>

    <script> 
        var JoyStick = (function(container){
			
			internalFillColor = '#CD2626';
            internalLineWidth = 2;
            internalStrokeColor = '#363636';
            externalLineWidth = 2;
            externalStrokeColor = '#008000';			
			
			objContainer = document.getElementById(container);
			
			var canvas = document.createElement('canvas');
			canvas.id = objContainer.clientTitle;
			canvas.width = objContainer.clientWidth;
            canvas.height = objContainer.clientHeight;
			canvas.border = objContainer.clientBorder;
						
			objContainer.appendChild(canvas);
			var context=canvas.getContext('2d');
			
			var pressed = 0;        
			
            var circumference = 2 * Math.PI;
            var internalRadius = (canvas.width-((50*2)+10))/2; //45
            var maxMoveStick = internalRadius + 5; //50
            var externalRadius = internalRadius + 30; //75
            var centerX = canvas.width / 2; //100
            var centerY = canvas.height / 2; //100
            var directionHorizontalLimitPos = canvas.width / 10; //20
            var directionHorizontalLimitNeg = directionHorizontalLimitPos * -1; //-20
            var directionVerticalLimitPos = canvas.height / 10; //20
            var directionVerticalLimitNeg = directionVerticalLimitPos * -1; //-20
            var movedX=centerX; //100
            var movedY=centerY; //100
            
			var touchable = 'createTouch' in document;
            if(touchable){
                canvas.addEventListener('touchstart', onTouchStart, false);
                canvas.addEventListener('touchmove', onTouchMove, false);
                canvas.addEventListener('touchend', onTouchEnd, false);
                }
            else{
                canvas.addEventListener('mousedown', onMouseDown, false);
                canvas.addEventListener('mousemove', onMouseMove, false);
                canvas.addEventListener('mouseup', onMouseUp, false);
                }
				
            drawExternal();
			
            drawInternal(centerX, centerY);
            
            function drawExternal(){
                context.beginPath();
                context.arc(centerX, centerY, externalRadius, 0, circumference, false);
                context.lineWidth = externalLineWidth;
                context.strokeStyle = externalStrokeColor;
                context.stroke();
                }
            
            function drawInternal(){
                context.beginPath();
                if(movedX<internalRadius) movedX=maxMoveStick;
                if((movedX+internalRadius)>canvas.width) movedX=canvas.width-(maxMoveStick);
                if(movedY<internalRadius) movedY=maxMoveStick;
                if((movedY+internalRadius)>canvas.height) movedY=canvas.height-(maxMoveStick);
                context.arc(movedX, movedY, internalRadius, 0, circumference, false);
                var grd = context.createRadialGradient(centerX, centerY, 5, centerX, centerY, 200);
                grd.addColorStop(0, internalFillColor);
                grd.addColorStop(1, internalStrokeColor);
                context.fillStyle = grd;
                context.fill();
                context.lineWidth = internalLineWidth;
                context.strokeStyle = internalStrokeColor;
                context.stroke();
                }
            
            function onTouchStart(event){
                pressed=1;
                }
            
            function onTouchMove(event) {
                event.preventDefault();
                if(pressed==1){
                    movedX=event.touches[0].pageX;
                    movedY=event.touches[0].pageY;
                    movedX-=canvas.offsetLeft;
                    movedY-=canvas.offsetTop;
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    drawExternal();
                    drawInternal();
                    }
                } 
            function onTouchEnd(event){
                pressed=0;
                movedX=centerX;
                movedY=centerY;
                context.clearRect(0, 0, canvas.width, canvas.height);
                drawExternal();
                drawInternal();
                }
            
            function onMouseDown(event){
                pressed=1;
                }
                
            function onMouseMove(event){
                if(pressed==1){
                    movedX=event.pageX;
                    movedY=event.pageY;
                    movedX-=canvas.offsetLeft;
                    movedY-=canvas.offsetTop;
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    drawExternal();
                    drawInternal();
                    }
                }
            
            function onMouseUp(event){
                pressed=0;
                movedX=centerX;
                movedY=centerY;
                context.clearRect(0, 0, canvas.width, canvas.height);
                drawExternal();
                drawInternal();
                }
                
            this.GetWidth = function (){
                return canvas.width;
                };
            this.GetHeight = function (){
                return canvas.height;
                };
            this.GetPosX = function (){
                return movedX;
                };
            this.GetPosY = function (){
                return movedY;
                };
            this.GetX = function (){
                return (100*((movedX - centerX)/maxMoveStick)).toFixed();
                };
            this.GetY = function (){
                return ((100*((movedY - centerY)/maxMoveStick))*-1).toFixed();
                };
            this.GetDir = function(){
                var result = "";
                var orizontal = movedX - centerX;
                var vertical = movedY - centerY;
                    if(vertical>=directionVerticalLimitNeg && vertical<=directionVerticalLimitPos){
                        result = "C";
                        }
                    if(vertical<directionVerticalLimitNeg){
                        result = "N";
                        }
                    if(vertical>directionVerticalLimitPos){
                        result = "S";
                        }
                    if(orizontal<directionHorizontalLimitNeg){
                        if(result=="C"){ 
                            result = "W";
                            }
                        else{
                            result += "W";
                            }
                        }
                    if(orizontal>directionHorizontalLimitPos){
                        if(result=="C"){ 
                            result = "W";
                            }
                        else{
                            result += "E";
                            }
                        }
                return result;
                };
            }
        );
    </script>
  </head>
  <body>
      <h1 id="titulo">Joystick Virtual</h1>
      
	  
	  <div id ="joy1">
          <div id="joyDiv" title="joystick1" style="width:200px;height:200px;margin-bottom:20px;border: 5px solid #1C1C1C;"></div>  
          Posizione X:<input id="posizioneX" type="text" /></br>
          Posizione Y:<input id="posizioneY" type="text" /></br>
          Direzione:<input id="direzione" type="text" /></br>
          X:<input id="X" type="text" /></br>
          Y :<input id="Y" type="text" />
      </div>

      <div id="joy2">
          <div id="joyDiv2" title="joystick2" style="width:200px;height:200px;margin-bottom:20px;border: 5px solid #1C1C1C;"></div> 
          Posizione J:<input id="posizioneJ" type="text" /></br>
          Posizione K:<input id="posizioneK" type="text" /></br>
          Direzione2:<input id="direzione2" type="text" /></br>
          J:<input id="J" type="text" /></br>
          K:<input id="K" type="text" />  
      </div>

      <script type="text/javascript">
          var coordAntes;
          var coord;
          
          var joy = new JoyStick('joyDiv');
          var inputPosX = document.getElementById("posizioneX");
          var inputPosY = document.getElementById("posizioneY");
          var direzione = document.getElementById("direzione");
          var x = document.getElementById("X");
          var y = document.getElementById("Y");

          setInterval(function(){ inputPosX.value=joy.GetPosX(); }, 50);
          setInterval(function(){ inputPosY.value=joy.GetPosY(); }, 50);
          setInterval(function(){ direzione.value=joy.GetDir(); }, 50);
          setInterval(function(){ x.value=joy.GetX(); }, 50);
          setInterval(function(){ y.value=joy.GetY(); }, 50);

          var joy2 = new JoyStick('joyDiv2');
          var inputPosJ = document.getElementById("posizioneJ");
          var inputPosK = document.getElementById("posizioneK");
          var direzione2 = document.getElementById("direzione2");
          var j = document.getElementById("J");
          var k = document.getElementById("K");

          setInterval(function(){ inputPosJ.value=joy2.GetPosX(); }, 50);
          setInterval(function(){ inputPosK.value=joy2.GetPosY(); }, 50);
          setInterval(function(){ direzione2.value=joy2.GetDir(); }, 50);
          setInterval(function(){ j.value=joy2.GetX(); }, 50);
          setInterval(function(){ k.value=joy2.GetY();       
              sendCoordenadas();
              }, 50);

          var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
          connection.onopen = function () {
              connection.send('Connect ' + new Date());
              };
          connection.onerror = function (error) {
              console.log('WebSocket Error ', error);
              };
          connection.onmessage = function (e) {
              console.log('Server: ', e.data);
              };
          connection.onclose = function () {
              console.log('WebSocket connection closed');
              document.location.reload(true);
              };
          function sendCoordenadas(){
              coordAntes = coord;
              var x = document.getElementById("X").value;
              var y = document.getElementById("Y").value;
              var j = document.getElementById("J").value;
              var k = document.getElementById("K").value; 
              coord = 'X: ' + x.toString(1) + '  Y: ' + y.toString(1) + '  J: ' + j.toString(1) + '  K: ' + k.toString(1);
              if(coordAntes != coord){  
                  console.log('Envia coordenadas: ' + coord);
                  connection.send(coord);
                  coordAntes = coord;
                  }
              else{
                  null;
                  }
              }         
    </script>
  </body>
</html> 
)=====";*/
