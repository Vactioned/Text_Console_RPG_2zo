---
name: Issue Template
about: 기본 이슈 템플런
title: "[Feat / Refactor / Style / .. ] 이슈 제목"
labels: ''
assignees: ''

---

## 📌 유형
- [ ] 신규 기능 (Feature)
- [ ] 버그 수정 (Bug Fix)
- [ ] 리팩토링 / 최적화 (Refactoring / Performance)
- [ ] 엔진 설정 / 플러그인 (Environment)

## 📖 설명
> 구현하고자 하는 기능의 목적과 핵심 내용을 간략히 적어주세요.

## 🛠️ 구현 상세 (C++ & Blueprint)
- **Base Class:** (예: `ACharacter`, `UActorComponent` 등 상속받을 클래스)
- **핵심 로직:** (구현할 주요 알고리즘이나 언리얼 API 활용 계획)
- **BP 노출:** (UFUNCTION, UPROPERTY 설정 범위 등)
- [ ] 세부 작업 내용 1...
- [ ] 세부 작업 내용 2...

## ⚠️ 현재 상황 및 문제점
<!-- 현재 발생 중인 에러 로그, 블루프린트 노드 꼬임, 혹은 성능 저하 요소를 설명해 주세요. -->

## 🎯 개선 목표
<!-- 무엇을 해결하고 싶은지 명확히 적어주세요. 예: "캐릭터 점프 시 발생하는 틱 지연 해결" -->

## 📝 수정 및 작업 계획
- [ ] 언리얼 네이밍 컨벤션 준수 (PascalCase, 접두사 A, U, F 등)
- [ ] 멀티플레이어 환경 고려 (필요 시 Replication 설정)
- [ ] 로그(UE_LOG) 및 주석 처리 확인
- [ ] 빌드 테스트 완료 (Win64 / Android 등)

## 📂 관련 에셋 경로
- **C++:** `Source/ProjectName/Public/..., Private/...`
- **Asset:** `/Game/Blueprints/..., /Game/Maps/...`

## 📸 추가 자료
스크린샷, 참고 영상, 혹은 외부 기술 문서 링크
