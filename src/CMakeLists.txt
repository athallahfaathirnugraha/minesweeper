set(SOURCE_FILES main.c)
set(HEADER_FILES minesweeper.h)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
