
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
<form action="select1.php" method="post">
<label>Choose an ice cream flavor:
      <p><select name="hr" id="hr">
      <option disabled>Get the time</option>
      <option value="00">00</option>
      <option value="01">01</option>
      <option value="02">02</option>
      <option value="03">03</option>
      <option value="04">04</option>
      <option value="05">05</option>
      <option value="06">06</option>
      <option value="07">07</option>
      <option value="08">08</option>
      <option value="09">09</option>
      <option value="10">10</option>
      <option value="11">11</option>
      <option value="12">12</option>
      <option value="13">13</option>
      <option value="14">14</option>
      <option value="15">15</option>
      <option value="16">16</option>
      <option value="17">17</option>
      <option value="18">18</option>
      <option value="19">19</option>
      <option value="20">20</option>
      <option value="21">21</option>
      <option value="22">22</option>
      <option value="23">23</option>
      </select>
      </label>
<div class="result"></div>
      <select name="min" id="min">
      <option disabled>Get the min</option>
      <option value="00">00</option>
      <option value="15">15</option>
      <option value="30">30</option>
      <option value="45">45</option>
      </select></p>
 </form>


     
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

          const selectElement = document.querySelector('.hr');
          selectElement.addEventListener('change', (event) => {
              const result = document.querySelector('.result');
              result.textContent = `You like ${event.target.value}`;
          });
<!--
          var hour = document.querySelector(".hr");<!--созд переменную реле считывующию значение hr-->
          function hour_go(){
              const log = document.getElementById('log');
              const selection = event.target.value.substring(event.target.selectionStart, event.target.selectionEnd);
           log.textContent = `You selected: ${selection}`;
              var request1 = new XMLHttpRequest();
              request1.open('GET','/hr00',false);
              request1.send();
              
            }
          
         hour.addEventListener('select', hour_go);

-->

          
         <!-- let hour = hr.value;--><!--созд переменную реле считывующию значение времени от пользователя-->
          <!--console.log(hour);-->
          <!--alert(hour);-->

       
           
          
    </script>
         
  </CENTER> 
</BODY>
</HTML>
)=====";
