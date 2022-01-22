
const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <TITLE>IR Remout</TITLE>
      <style>
          body{
            text-align: center;
            heigh: 100%;
            margin: 10;
          }
          input[type="button"] {
              position: relative;
              top: 50%;
              <!-- // margin-left: 6px;  положение относительно других обьектов-->
              padding: 6px 6px;
              border-radius: 80px;
             
              width: 20%;
              font-size: 24px;
          }
      .but_on{
        opacity: 1;
       }
      .but_off{
        opacity: 0.6;
       }
      
      </style>
    
      
  </HEAD>
<BODY>
    <CENTER>
        <B>IR Remout</B>
        <p></p>
        <br>
        <input type="button" value="+" id="FF3AC5" style=" color: #000000; background-color: white">  <!-- //кнопка-->
        <input type="button" value="-" id="FFBA45" style=" color: #000000; background-color: white">
        <input type="button" value=">|" id="FF827D" style="color: #FFFFFF; background-color: #000000">
        <input type="button" value="OFF"id="FF02FD" style="color: #FFFFFF; background-color: #ff0000">

        <input type="button" value="R" id="FF1AE5" style="color: #000000; background-color: #ff0000">
        <input type="button" value="G" id="FF9A65" style="color: #000000; background-color: #4CAF50">
        <input type="button" value="B" id="FFA25D" style="color: #000000; background-color: #0c27a3">
        <input type="button" value="W" id="FF22DD" style="color: #000000; background-color: white">

        <input type="button" value="1" id="FF2AD5" style="color: #000000; background-color: #ff6a00">
        <input type="button" value="2" id="FFAA55" style="color: #000000; background-color: #00ff21">
        <input type="button" value="3" id="FF926D" style="color: #000000; background-color: #0094ff">
        <input type="button" value="4" id="FF12ED" style="color: #000000; background-color: #c879c3">

        <input type="button" value="5" id="FF0AF5" style="color: #000000; background-color: #e2c109">
        <input type="button" value="6" id="FF8A75" style="color: #000000; background-color: #5fbcb7">
        <input type="button" value="7" id="FFB24D" style="color: #000000; background-color: #b200ff">
        <input type="button" value="8" id="FF32CD" style="color: #000000; background-color: #c879c3">

        <input type="button" value="9" id="FF38C7"  style=" color: #000000; background-color: #dea142">
        <input type="button" value="10" id="FFB847" style=" color: #000000; background-color: #2e7f9b">
        <input type="button" value="11" id="FF7887" style=" color: #000000; background-color: #b23dbb">
        <input type="button" value="12" id="FFF807" style=" color: #000000; background-color: #36accb">

        <input type="button" value="13" id="FF18E7" style=" color: #000000; background-color: #e2c109">
        <input type="button" value="14" id="FF9867" style=" color: #000000; background-color: #1b696c">
        <input type="button" value="15" id="FF58A7" style=" color: #000000; background-color: #d6a7e8">
        <input type="button" value="16" id="FFD827" style=" color: #000000; background-color: #36accb">

        <input type="button" value="/\" id="FF28D7" style=" color: #ff0000; background-color: white">
        <input type="button" value="/\" id="FFA857" style=" color: #4CAF50; background-color: white">
        <input type="button" value="/\" id="FF6897" style=" color: #0094ff; background-color: white">
        <input type="button" value="QUICK" id="FFE817"style=" color: #000000; background-color: white">

        <input type="button" value="\/" id="FF08F7" style=" color: #ff0000; background-color: white">
        <input type="button" value="\/" id="FF8877" style=" color: #4CAF50; background-color: white">
        <input type="button" value="\/" id="FF48B7" style=" color: #0094ff; background-color: white">
        <input type="button" value="SLOW" id="FFC837" style=" color: #000000; background-color: white">


        <input type="button" value="DIY1" id="FF30CF" style=" color: #000000; background-color: white">
        <input type="button" value="DIY2" id="FFB04F" style=" color: #000000; background-color: white">
        <input type="button" value="DIY3" id="FF708F" style=" color: #000000; background-color: white">
        <input type="button" value="AUTO" id="FFF00F" style=" color: #000000; background-color: white">

        <input type="button" value="DIY4" id="FF10EF" style=" color: #000000; background-color: white">
        <input type="button" value="DIY5" id="FF906F" style=" color: #000000; background-color: white">
        <input type="button" value="DIY6" id="FF50AF" style=" color: #000000; background-color: white">
        <input type="button" value="FLASH"id="FFD02F" style=" color: #000000; background-color: white">

        <input type="button" value="JUMP4" id="FF20DF" style=" color: #000000; background-color: white">
        <input type="button" value="JUMP7" id="FFA05F" style=" color: #000000; background-color: white">
        <input type="button" value="FADE3" id="FF609F" style=" color: #000000; background-color: white">
        <input type="button" value="FADE7" id="FFE01F" style=" color: #000000; background-color: white">

        <input type="button" value="Svet" id="Svet_but" class="">  <!-- //кнопка-->
        <!--//<br>-->
        <!-- // <input type="radio" name="test" value="1"> One<Br>  --> <!-- //кружочки с точко можно выбрать 1 из всех-->
        <!--// <input type="radio" name="test" value="2"> Two<Br>-->
        <!--// <input type="radio" name="test" value="3"> 3<Br>-->


        <script>
              var relay = document.getElementById("Svet_but"); <!--созд переменную реле считывующию значение Свет бат-->
              var FF3AC5__ = document.getElementById("FF3AC5"); <!--0-->
              var FFBA45__ = document.getElementById("FFBA45"); <!--1-->
              var FF827D__ = document.getElementById("FF827D"); <!--2-->
              var FF02FD__ = document.getElementById("FF02FD"); <!--3-->
              var FF1AE5__ = document.getElementById("FF1AE5"); <!--4-->
              var FF9A65__ = document.getElementById("FF9A65"); <!--5-->
              var FFA25D__ = document.getElementById("FFA25D"); <!--6-->
              var FF22DD__ = document.getElementById("FF22DD"); <!--7-->
              var FF2AD5__ = document.getElementById("FF2AD5"); <!--8-->
              var FFAA55__ = document.getElementById("FFAA55"); <!--9-->
              var FF926D__ = document.getElementById("FF926D"); <!--10-->
              var FF12ED__ = document.getElementById("FF12ED"); <!--11-->
              var FF0AF5__ = document.getElementById("FF0AF5"); <!--12-->
              var FF8A75__ = document.getElementById("FF8A75"); <!--13-->
              var FFB24D__ = document.getElementById("FFB24D"); <!--14-->
              var FF32CD__ = document.getElementById("FF32CD"); <!--15-->
              var FF38C7__ = document.getElementById("FF38C7"); <!--16-->
              var FFB847__ = document.getElementById("FFB847"); <!--17-->
              var FF7887__ = document.getElementById("FF7887"); <!--18-->
              var FFF807__ = document.getElementById("FFF807"); <!--19-->
              var FF18E7__ = document.getElementById("FF18E7"); <!--20-->
              var FF9867__ = document.getElementById("FF9867"); <!--21-->
              var FF58A7__ = document.getElementById("FF58A7"); <!--22-->
              var FFD827__ = document.getElementById("FFD827"); <!--23-->
              var FF28D7__ = document.getElementById("FF28D7"); <!--24-->
              var FFA857__ = document.getElementById("FFA857"); <!--25-->
              var FF6897__ = document.getElementById("FF6897"); <!--26-->
              var FFE817__ = document.getElementById("FFE817"); <!--27-->
              var FF08F7__ = document.getElementById("FF08F7"); <!--28-->
              var FF8877__ = document.getElementById("FF8877"); <!--29-->
              var FF48B7__ = document.getElementById("FF48B7"); <!--30-->
              var FFC837__ = document.getElementById("FFC837"); <!--31-->
              var FF30CF__ = document.getElementById("FF30CF"); <!--32-->
              var FFB04F__ = document.getElementById("FFB04F"); <!--33-->
              var FF708F__ = document.getElementById("FF708F"); <!--34-->
              var FFF00F__ = document.getElementById("FFF00F"); <!--35-->
              var FF10EF__ = document.getElementById("FF10EF"); <!--36-->
              var FF906F__ = document.getElementById("FF906F"); <!--37-->
              var FF50AF__ = document.getElementById("FF50AF"); <!--38-->
              var FFD02F__ = document.getElementById("FFD02F"); <!--39-->
              var FF20DF__ = document.getElementById("FF20DF"); <!--40-->
              var FFA05F__ = document.getElementById("FFA05F"); <!--41-->
              var FF609F__ = document.getElementById("FF609F"); <!--42-->
              var FFE01F__ = document.getElementById("FFE01F"); <!--43-->




            
            var relay_stastus = 0;
            function relay_state() {
                var request = new XMLHttpRequest();
                request.open('GET', '/relay_status', true);
                request.onload = function () {
                    if (request.readyState == 4 && request.status == 200) {
                        var response = request.responseText;
                        relay_status = Number.parseInt(response);
                        if (relay_status == 0)
                            relay.classList.add('but_off');
                        else
                            relay.classList.add('but_on');
                    }
                }
                request.send();
            }




            function relay_inverse() {
                var request = new XMLHttpRequest();
                request.open('GET', '/relay_switch', false);
                request.send();

                if (request.readyState == 4 && request.status == 200) {
                    var response = request.responseText;
                    relay_status = Number.parseInt(response);
                    if (relay_status == 0) {
                        relay.classList.remove('but_on');
                        relay.classList.add('but_off');
                    }
                    else {
                        relay.classList.remove('but_off');
                        relay.classList.add('but_on');
                    }
                }

            }
            
              function FF3AC5_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF3AC5', false);
                  request.send();
              }
              function FFBA45_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFBA45', false);
                  request.send();
              }
              function FF827D_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF827D', false);
                  request.send();
              }
              function FF02FD_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF02FD', false);
                  request.send();
              }
              function FF1AE5_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF1AE5', false);
                  request.send();
              }
              function FF9A65_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF9A65', false);
                  request.send();
              }
              function FFA25D_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFA25D', false);
                  request.send();
              }
              function FF22DD_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF22DD', false);
                  request.send();
              }
              function FF2AD5_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF2AD5', false);
                  request.send();
              }
              function FFAA55_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFAA55', false);
                  request.send();
              }
              function FF926D_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF926D', false);
                  request.send();
              }
              function FF12ED_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF12ED', false);
                  request.send();
              }
              function FF0AF5_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF0AF5', false);
                  request.send();
              }
              function FF8A75_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF8A75', false);
                  request.send();
              }
              function FFB24D_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFB24D', false);
                  request.send();
              }
              function FF32CD_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF32CD', false);
                  request.send();
              }
              function FF38C7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF38C7', false);
                  request.send();
              }
              function FFB847_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFB847', false);
                  request.send();
              }
              function FF7887_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF7887', false);
                  request.send();
              }
              function FFF807_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFF807', false);
                  request.send();
              }
              function FF18E7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF18E7', false);
                  request.send();
              }
              function FF9867_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF9867', false);
                  request.send();
              }
              function FF58A7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF58A7', false);
                  request.send();
              }
              function FFD827_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFD827', false);
                  request.send();
              }
              function FF28D7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF28D7', false);
                  request.send();
              }
              function FFA857_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFA857', false);
                  request.send();
              }
              function FF6897_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF6897', false);
                  request.send();
              }
              function FFE817_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFE817', false);
                  request.send();
              }
              function FF08F7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF08F7', false);
                  request.send();
              }
              function FF8877_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF8877', false);
                  request.send();
              }
              function FF48B7_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF48B7', false);
                  request.send();
              }
              function FFC837_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFC837', false);
                  request.send();
              }
              function FF30CF_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF30CF', false);
                  request.send();
              }
              function FFB04F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFB04F', false);
                  request.send();
              }
              function FF708F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF708F', false);
                  request.send();
              }
              function FFF00F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFF00F', false);
                  request.send();
              }
              function FF10EF_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF10EF', false);
                  request.send();
              }
              function FF906F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF906F', false);
                  request.send();
              }
              function FF50AF_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF50AF', false);
                  request.send();
              }
              function FFD02F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFD02F', false);
                  request.send();
              }
              function FF20DF_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF20DF', false);
                  request.send();
              }
              function FFA05F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFA05F', false);
                  request.send();
              }
              function FF609F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FF609F', false);
                  request.send();
              }
              function FFE01F_() {
                  var request = new XMLHttpRequest();
                  request.open('GET', '/FFE01F', false);
                  request.send();
              }



            document.addEventListener('DOMContentLoaded', relay_state);
              relay.addEventListener('click', relay_inverse);
              FF3AC5__.addEventListener('click', FF3AC5_); <!--0-->
              FFBA45__.addEventListener('click', FFBA45_); <!--1-->
              FF827D__.addEventListener('click', FF827D_); <!--2-->
              FF02FD__.addEventListener('click', FF02FD_); <!--3-->
        

              FF1AE5__.addEventListener('click', FF1AE5_); <!--4-->
              FF9A65__.addEventListener('click', FF9A65_); <!--5-->
              FFA25D__.addEventListener('click', FFA25D_); <!--6-->
              FF22DD__.addEventListener('click', FF22DD_); <!--7-->
              FF2AD5__.addEventListener('click', FF2AD5_); <!--8-->
              FFAA55__.addEventListener('click', FFAA55_); <!--9-->
              FF926D__.addEventListener('click', FF926D_); <!--10-->
              FF12ED__.addEventListener('click', FF12ED_); <!--11-->
              FF0AF5__.addEventListener('click', FF0AF5_); <!--12-->
              FF8A75__.addEventListener('click', FF8A75_); <!--13-->
              FFB24D__.addEventListener('click', FFB24D_); <!--14-->
              FF32CD__.addEventListener('click', FF32CD_); <!--15-->
              FF38C7__.addEventListener('click', FF38C7_); <!--16-->
              FFB847__.addEventListener('click', FFB847_); <!--17-->
              FF7887__.addEventListener('click', FF7887_); <!--18-->
              FFF807__.addEventListener('click', FFF807_); <!--19-->
              FF18E7__.addEventListener('click', FF18E7_); <!--20-->
              FF9867__.addEventListener('click', FF9867_); <!--21-->
              FF58A7__.addEventListener('click', FF58A7_); <!--22-->
              FFD827__.addEventListener('click', FFD827_); <!--23-->
              FF28D7__.addEventListener('click', FF28D7_); <!--24-->
              FFA857__.addEventListener('click', FFA857_); <!--25-->
              FF6897__.addEventListener('click', FF6897_); <!--26-->
              FFE817__.addEventListener('click', FFE817_); <!--27-->
              FF08F7__.addEventListener('click', FF08F7_); <!--28-->
              FF8877__.addEventListener('click', FF8877_); <!--29-->
              FF48B7__.addEventListener('click', FF48B7_); <!--30-->
              FFC837__.addEventListener('click', FFC837_); <!--31-->
              FF30CF__.addEventListener('click', FF30CF_); <!--32-->
              FFB04F__.addEventListener('click', FFB04F_); <!--33-->
              FF708F__.addEventListener('click', FF708F_); <!--34-->
              FFF00F__.addEventListener('click', FFF00F_); <!--35-->
              FF10EF__.addEventListener('click', FF10EF_); <!--36-->
              FF906F__.addEventListener('click', FF906F_); <!--37-->
              FF50AF__.addEventListener('click', FF50AF_); <!--38-->
              FFD02F__.addEventListener('click', FFD02F_); <!--39-->
              FF20DF__.addEventListener('click', FF20DF_); <!--40-->
              FFA05F__.addEventListener('click', FFA05F_); <!--41-->
              FF609F__.addEventListener('click', FF609F_); <!--42-->
              FFE01F__.addEventListener('click', FFE01F_); <!--43-->
        </script>

    </CENTER> 
</BODY>
</HTML>
)=====";
