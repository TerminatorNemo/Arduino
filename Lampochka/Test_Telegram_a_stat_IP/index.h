
const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <TITLE>Lampochka</TITLE>
      <style>
          body{
            text-align: center;
            heigh: 100%;
            margin: 10;
          }
        input[type="button"] {
            position: relative;
            top: 50%;
            margin-top: -30px;
            padding: 16px 64px;
            border-radius: 8px;
            background-color: #4CAF50;
            width: 50%;

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
      <B>My HOME </B>
      <p></p>
      <br>
       <input type="button" value="Svet" id="Svet_but" class="">  <!-- //кнопка-->
     
   <!--//<br>-->
   <!-- // <input type="radio" name="test" value="1"> One<Br>  --> <!-- //кружочки с точко можно выбрать 1 из всех-->
    <!--// <input type="radio" name="test" value="2"> Two<Br>-->
    <!--// <input type="radio" name="test" value="3"> 3<Br>-->


      <script>
          var relay = document.getElementById("Svet_but");<!--созд переменную реле считывующию значение Свет бат-->
          var relay_stastus = 0;
          function relay_state(){
            var request = new XMLHttpRequest();
            request.open('GET','/relay_status',true);
            request.onload=function(){
              if(request.readyState==4 && request.status == 200){
                var response = request.responseText;
                relay_status=Number.parseInt(response);
                if(relay_status==0)
                  relay.classList.add('but_off');
                else
                  relay.classList.add('but_on');
              }  
            }
            request.send();
          }
          function relay_inverse() {
            var request = new XMLHttpRequest();
            request.open('GET','/relay_switch',false);
            request.send();
          
            if(request.readyState == 4 && request.status == 200){
                var response = request.responseText;
                relay_status=Number.parseInt(response);
                if(relay_status==0){
                  relay.classList.remove('but_on');
                  relay.classList.add('but_off');
                }
                else{
                  relay.classList.remove('but_off');
                  relay.classList.add('but_on');
                }
            }
            
          }
          document.addEventListener('DOMContentLoaded',relay_state);
          relay.addEventListener('click', relay_inverse);
    </script>
         
  </CENTER> 
</BODY>
</HTML>
)=====";
