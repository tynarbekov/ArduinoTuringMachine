#include <LiquidCrystal.h>
int Con = 20;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int disPos = 0, startPos = 0, endPos = 15;
bool lap = false;
char text[16], empty = '*';

void setup() {
  Serial.begin(9600);
  analogWrite(6,20);
  lcd.begin(16,2);

  char temp[] = "1264321";
  clearText();
  setText(temp);
  isPalindrome();
}
void loop(){
}


void isPalindrome(){
  // direction true = move right, false = move left
  bool dir = true, reverse = false, isPalin = true;
  char tempChar = empty, current = empty;
  while(true){
    if(startPos == endPos || (tempChar == empty && startPos == endPos - 1)){
      Serial.println("PALINDROME");
      break;
    }
    current = text[disPos];
    Serial.print("-current: '");
    Serial.print(current);
    Serial.println("'");
    if(current != empty && tempChar != empty){
      !!dir ? moveRight() : moveLeft();
      delay(500);
      continue;
    }
    if(tempChar != empty && current == empty){
      dir = !dir;
    }
    !!dir ? moveRight() : moveLeft();
    current = text[disPos];
    delay(500);
    if(tempChar == empty){
      tempChar = current;
      clearCurrent();
      !!dir ? moveRight() : moveLeft();
      continue;
    }
    if(tempChar != empty && tempChar == current){
      tempChar = current;
      clearCurrent();
      tempChar = empty;
      !!dir ? moveRight() : moveLeft();
      delay(500);
      tempChar = text[disPos];
      clearCurrent();
      delay(500);
      !!dir ? moveRight() : moveLeft();
      current = text[disPos];
      if(current == empty){
        break;
      }
      continue;
    }else{
      isPalin = false;
      break;
    }

    delay(500);

  }
  delay(1000);
  clearText();
  if(isPalin)
    setText("palin");
  else
    setText("not palin");
  lcd.print(text);
  Serial.print(text);
}

void setPos(int x){
  lcd.setCursor(disPos,1);
  lcd.print(" ");

  lcd.setCursor(x,1);
  lcd.print("^");

  lcd.setCursor(x,0);
  disPos = x;
}

void initPos(){
  setPos(0);
}

void setText(char value[]){
    clearText();
    if(strlen(value) > 15){
      Serial.print("too long text");
      lcd.print("too long");
      return;
    }

    int len = strlen(value) / 2;
    startPos = 8 - len;
    endPos = startPos + strlen(value) - 1;
    int valId = 0;
    for(int disId  = startPos; disId <= endPos; disId++){
      text[disId] = value[valId];
      valId += 1;
    }
    setPos(0);
    lcd.print(text);
    startPos--;
    setPos(startPos);
}

/**
 * moves cusor left
 * return true if possible
 * return false if can't
 */
bool moveLeft(){
  if(disPos <= 0) {
    return false;
  }
  setPos(disPos - 1);
  return true;
};

/**
 * moves cusor right
 * return true if possible
 * return false if can't
 */
bool moveRight(){
  if(disPos >= 15) {
    return false;
  }
  setPos(disPos + 1);
  return true;
};
void clearCurrent(){
  lcd.print(empty);
  text[disPos] = '*';
  if(disPos <= 7)
    startPos = disPos;
  else
    endPos = disPos;
}
void clearText(){
  for(int i = 0; i < 16; i++){
    text[i] = empty;
  }
//  lcd.clear();
  initPos();
}

void printError(char msg[]){
  lcd.clear();
  initPos();
  lcd.print("ERROR: ");
  lcd.print(msg);
}
