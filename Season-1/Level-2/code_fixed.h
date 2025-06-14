#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 39
#define SETTINGS_COUNT 10
#define MAX_USERS 100
#define INVALID_USER_ID -1

int userid_next = 0;

typedef struct {
    char username[MAX_USERNAME_LEN + 1];
    bool isAdmin;
    long userid;
    long setting[SETTINGS_COUNT];
} user_account;

user_account *accounts[MAX_USERS];

// 계정 생성 함수
int create_user_account(bool isAdmin, const char *username) {
    if (userid_next >= MAX_USERS) {
        fprintf(stderr, "the maximum number of users have been exceeded\n");
        return INVALID_USER_ID;
    }

    if (strlen(username) > MAX_USERNAME_LEN) {
        fprintf(stderr, "the username is too long\n");
        return INVALID_USER_ID;
    }

    user_account *ua = (user_account *)malloc(sizeof(user_account));    
    if (ua == NULL) {
        fprintf(stderr, "malloc failed to allocate memory\n");
        return INVALID_USER_ID;
    }

    ua->isAdmin = isAdmin;
    ua->userid = userid_next;
    memset(&ua->setting, 0, sizeof ua->setting);
    strncpy(ua->username, username, MAX_USERNAME_LEN);
    ua->username[MAX_USERNAME_LEN] = '\0';  // 명시적 종료

    accounts[userid_next] = ua;
    return userid_next++;
}

// 사용자 이름 업데이트 함수
bool update_username(int user_id, const char *new_name) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL)
        return false;

    size_t curr_len = strlen(accounts[user_id]->username);
    size_t remain = MAX_USERNAME_LEN - curr_len;

    if (remain == 0)
        return false;

    strncat(accounts[user_id]->username, new_name, remain);
    accounts[user_id]->username[MAX_USERNAME_LEN] = '\0';  // 종료 보장
    return true;
}

// 사용자 설정 변경
bool update_setting(int user_id, const char *index, const char *value) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL)
        return false;

    char *endptr;
    long i = strtol(index, &endptr, 10);
    if (*endptr) return false;

    long v = strtol(value, &endptr, 10);
    if (*endptr || i < 0 || i >= SETTINGS_COUNT)
        return false;

    accounts[user_id]->setting[i] = v;
    return true;
}

// 관리자 권한 여부 확인
bool is_admin(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "invalid user id\n");
        return false;
    }
    return accounts[user_id]->isAdmin;
}

// 사용자 이름 반환
const char* username(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "invalid user id\n");
        return NULL;
    }
    return accounts[user_id]->username;
}
