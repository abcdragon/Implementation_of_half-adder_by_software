typedef struct half_adder {
  int S, C;
};

bool NOT(int A) {
  return ( !A );
}
bool OR(int A, int B) {
  return ( A | B );
}
bool AND(int A, int B) {
  return ( A & B );
}
bool XOR(int A, int B) {
  return ( AND( NOT( AND( A, B ) ), OR( A, B ) ) );
}

void halfCalc(half_adder& ha, int A, int B) {
  ha.S = XOR(A, B);
  ha.C = AND(A, B);
}

void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP); pinMode(11, INPUT_PULLUP); pinMode(10, INPUT_PULLUP);
  pinMode(9, OUTPUT); pinMode(8, OUTPUT);
}

void loop() {
  int A = !digitalRead(12); // C1;
  int B = !digitalRead(11); // S2(임시);
  int C = !digitalRead(10); // C2;

  Serial.print("A : ");
  Serial.print(A);
  Serial.print(" B : ");
  Serial.print(B);
  Serial.print(" C : ");
  Serial.println(C);

  half_adder ha;
  halfCalc(ha, A, B); // ha.S : S2(최종), ha.C : C3(임시)

  digitalWrite(9, OR( C, ha.C ));
  digitalWrite(8, ha.S);
}
