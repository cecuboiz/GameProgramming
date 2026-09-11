<img width="495" height="367" alt="image" src="https://github.com/user-attachments/assets/bfd4939a-e121-4b9c-a9d1-3c74b06d928c" />

# C언어 `scanf` 입력 버퍼(Input Buffer) 문제 해결

## 🚨 문제 (Problem)
C언어에서 `scanf("%s", string);`로 문자열을 입력받은 후, 이어서 `scanf("%c", &c);`로 문자를 입력받으려 할 때 **문자 입력이 씹히고(무시되고) 프로그램이 넘어가는 현상**이 자주 발생합니다.

**원인:** 
문자열을 입력하고 누른 **엔터(개행 문자 `\n`)**가 입력 버퍼(Input Buffer)에 그대로 남아있기 때문입니다. 따라서 다음 `scanf`가 사용자의 입력을 기다리지 않고 버퍼에 남아있는 `\n`을 가져가 버립니다.

---

## 💡 해결 방법 (Solutions)
입력 버퍼에 남은 개행 문자를 비워주면 해결됩니다. 상황에 맞게 다음 방법들을 사용할 수 있습니다.

### 1. `scanf`에 공백 추가 (가장 추천 ⭐)
`%c` 앞에 **공백(Space)**을 하나 추가하면, 버퍼에 남은 공백이나 개행 문자를 무시하고 실제 문자만 입력받습니다.
```c
scanf(" %c", &c);
2. getchar(); 사용
두 scanf 사이에 getchar(); 함수를 삽입하여 버퍼에 남은 \n을 강제로 소모시킵니다.
scanf("%s", string);
getchar(); // 버퍼 비우기
scanf("%c", &c);
3. fgets() 사용 (안전한 입력)
scanf 대신 fgets를 사용하여 줄 바꿈까지 통째로 입력받고, 문자열 끝에 추가된 개행 문자를 널 문자(\0)로 바꿔주는 방식입니다.

fgets(string, sizeof(string), stdin);
string[strlen(string)-1] = '\0';
