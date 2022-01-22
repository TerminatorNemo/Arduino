
const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <TITLE>My HOME</TITLE>
      <style>
          body{
            text-align: center;
            heigh: 100%;
            margin: 10;
          }

        input[class="button2"] {
            position: relative;
            top: 50%;
            margin-top: 20px;
            padding: 16px 64px;
            border-radius: 8px;
            background-color: #4CAF50;
            width: 50%;

            font-size: 24px;
      }
      input [class="min"]{
          position: left;
                    margin-left: 120px;
                    margin-top: 120px;
        }
      input [class="hr"]{
            left: -120px;
                    margin-top: 50px;    
        }
        
      .but_on{
        opacity: 1;
        position: relative;
        top: 50%;
        margin-top: -30px;
        padding: 16px 64px;
        border-radius: 8px;
        background-color: #4CAF50;
        width: 50%;
        font-size: 24px;
       }
      .but_off{
        opacity: 0.6;
        position: relative;
        top: 50%;
        margin-top: -30px;
        padding: 16px 64px;
        border-radius: 8px;
        background-color: #4CAF50;
        width: 50%;
        font-size: 24px;
       }

      
      </style>
    
      
  </HEAD>
<BODY>
  <CENTER>
      <B>My HOME </B>
      <p></p>
      <br>
      <input type="button" value="Svet"  id="Svet_but" class="but_on" >  <!-- //кнопка-->
      <input type="button" value="blink" id="blink"    class="button2">  <!-- //кнопка-->
     
      <br>
    <input type="radio" id="radio1" name="test" value="1" class="hr"> <label for="radio1" >1</label> <Br>  <!-- //кружочки с точко можно выбрать 1 из всех-->
    <input type="radio" id="radio2" name="test" value="2" class="hr"> <label for="radio2" >2</label> <Br>
    <input type="radio" id="radio3" name="test" value="3" class="hr"> <label for="radio3" >3</label> <Br>
    <input type="radio" id="radio4" name="test" value="4" class="hr"> <label for="radio4" >4</label> <Br>
    <input type="radio" id="radio5" name="test" value="5" class="hr"> <label for="radio5" >5</label> <Br>
    <input type="radio" id="radio6" name="test" value="6" class="hr"> <label for="radio6" >6</label> <Br>
    <input type="radio" id="radio7" name="test" value="7" class="hr"> <label for="radio7" >7</label> <Br>
    <input type="radio" id="radio8" name="test" value="8" class="hr"> <label for="radio8" >8</label> <Br>
    <input type="radio" id="radio9" name="test" value="9" class="hr"> <label for="radio9" >9</label> <Br>
    <input type="radio" id="radio10"name="test" value="10"class="hr"> <label for="radio10">10</label><Br>
    <input type="radio" id="radio11"name="test" value="11"class="hr"> <label for="radio11">11</label><Br>


    <input type="radio" id="min1" name="min" value="1" class="min"> <label for="min1" >1</label> <Br>  <!-- //кружочки с точко можно выбрать 1 из всех-->
    <input type="radio" id="min2" name="min" value="2" class="min"> <label for="min2" >2</label> <Br>
    <input type="radio" id="min3" name="min" value="3" class="min"> <label for="min3" >3</label> <Br>
    <input type="radio" id="min4" name="min" value="4" class="min"> <label for="min4" >4</label> <Br>
    <input type="radio" id="min5" name="min" value="5" class="min"> <label for="min5" >5</label> <Br>
    <input type="radio" id="min6" name="min" value="6" class="min"> <label for="min6" >6</label> <Br>
    <input type="radio" id="min7" name="min" value="7" class="min"> <label for="min7" >7</label> <Br>
    <input type="radio" id="min8" name="min" value="8" class="min"> <label for="min8" >8</label> <Br>
    <input type="radio" id="min9" name="min" value="9" class="min"> <label for="min9" >9</label> <Br>
    <input type="radio" id="min10"name="min" value="10"class="min"> <label for="min10">10</label><Br>
    <input type="radio" id="min11"name="min" value="11"class="min"> <label for="min11">11</label><Br>
      <script>
         var relay = document.getElementById("Svet_but");<!--созд переменную реле считывующию значение Свет бат-->
         var blink1 = document.getElementById("blink");<!--созд переменную реле считывующию значение blink-->
         var relay_stastus = 0;
         function relay_inverse_radio_start(){
            if(document.getElementById("radio5").checked){
                for(var i=1;i<11;i++){
                   setTimeout(relay_inverse_radio,i*500);
                   
                }
            } 
            relay_state();
         }
         
        function relay_inverse_radio(){
                         
            var request = new XMLHttpRequest();
            request.open('GET','/relay_switch',false);
            request.send();

        } 
          
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
          blink1.addEventListener('click', relay_inverse_radio_start);
    </script>
         
  </CENTER> 
</BODY>
</HTML>
)=====";
