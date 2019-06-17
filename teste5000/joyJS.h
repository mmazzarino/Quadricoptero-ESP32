const char joyJs[] PROGMEM = R"=====(
var JoyStick = (function(container, parameters) {
parameters = parameters || {};
var title = (undefined === parameters.title ? 'joystick' : parameters.title),
width = (undefined === parameters.width ? 0 : parameters.width),
height = (undefined === parameters.height ? 0 : parameters.height),
internalFillColor = (undefined === parameters.internalFillColor ? '#CD2626' : parameters.internalFillColor),
internalLineWidth = (undefined === parameters.internalLineWidth ? 2 : parameters.internalLineWidth),
internalStrokeColor = (undefined === parameters.internalStrokeColor ? '#363636' : parameters.internalStrokeColor),
externalLineWidth = (undefined === parameters.externalLineWidth ? 2 : parameters.externalLineWidth),
externalStrokeColor = (undefined === parameters.externalStrokeColor ? '#008000' : parameters.externalStrokeColor);
var objContainer = document.getElementById(container);
var canvas = document.createElement('canvas');
canvas.id = title;
if(width == 0) width = objContainer.clientWidth;
if(height == 0) height = objContainer.clientHeight;
canvas.width = width;
canvas.height = height;
objContainer.appendChild(canvas);
var context=canvas.getContext('2d');

var pressed = 0; // Bool - 1=Yes - 0=No
var circumference = 2 * Math.PI;
var internalRadius = (canvas.width-((50*2)+10))/2;
var maxMoveStick = internalRadius + 5;
var externalRadius = internalRadius + 30;
var centerX = canvas.width / 2;
var centerY = canvas.height / 2;
var directionHorizontalLimitPos = canvas.width / 10;
var directionHorizontalLimitNeg = directionHorizontalLimitPos * -1;
var directionVerticalLimitPos = canvas.height / 10;
var directionVerticalLimitNeg = directionVerticalLimitPos * -1;
var movedX=centerX;
var movedY=centerY;
var touchable = 'createTouch' in document;
if(touchable)
{
canvas.addEventListener('touchstart', onTouchStart, false);
canvas.addEventListener('touchmove', onTouchMove, false);
canvas.addEventListener('touchend', onTouchEnd, false);
}
else
{
canvas.addEventListener('mousedown', onMouseDown, false);
canvas.addEventListener('mousemove', onMouseMove, false);
canvas.addEventListener('mouseup', onMouseUp, false);
}
drawExternal();
drawInternal(centerX, centerY);
function drawExternal()
{
context.beginPath();
context.arc(centerX, centerY, externalRadius, 0, circumference, false);
context.lineWidth = externalLineWidth;
context.strokeStyle = externalStrokeColor;
context.stroke();
}
function drawInternal()
{
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
function onTouchStart(event) 
{
pressed=1;
}
function onTouchMove(event) {
event.preventDefault();
if(pressed==1)
{
movedX=event.touches[0].pageX;
movedY=event.touches[0].pageY;
movedX-=canvas.offsetLeft;
movedY-=canvas.offsetTop;
context.clearRect(0, 0, canvas.width, canvas.height);
drawExternal();
drawInternal();
}
} 
function onTouchEnd(event) 
{
pressed=0;
movedX=centerX;
movedY=centerY;
context.clearRect(0, 0, canvas.width, canvas.height);
drawExternal();
drawInternal();
}
function onMouseDown(event) 
{
pressed=1;
}
function onMouseMove(event) 
{
if(pressed==1)
{
movedX=event.pageX;
movedY=event.pageY;
movedX-=canvas.offsetLeft;
movedY-=canvas.offsetTop;
context.clearRect(0, 0, canvas.width, canvas.height);
drawExternal();
drawInternal();
}
}
function onMouseUp(event) 
{
pressed=0;
movedX=centerX;
movedY=centerY;
context.clearRect(0, 0, canvas.width, canvas.height);
drawExternal();
drawInternal();
}
this.GetWidth = function () 
{
return canvas.width;
};
this.GetHeight = function () 
{
return canvas.height;
};
this.GetPosX = function ()
{
return movedX;
};
this.GetPosY = function ()
{
return movedY;
};
this.GetX = function ()
{
return (100*((movedX - centerX)/maxMoveStick)).toFixed();
};
this.GetY = function ()
{
return ((100*((movedY - centerY)/maxMoveStick))*-1).toFixed();
};
this.GetDir = function()
{
var result = "";
var orizontal = movedX - centerX;
var vertical = movedY - centerY;
if(vertical>=directionVerticalLimitNeg && vertical<=directionVerticalLimitPos)
{
result = "C";
}
if(vertical<directionVerticalLimitNeg)
{
result = "N";
}
if(vertical>directionVerticalLimitPos)
{
result = "S";
}
if(orizontal<directionHorizontalLimitNeg)
{
if(result=="C")
{ 
result = "W";
}
else
{
result += "W";
}
}
if(orizontal>directionHorizontalLimitPos)
{
if(result=="C")
{ 
result = "W";
}
else
{
result += "E";
}
}
return result;
};
}
);
)=====";
