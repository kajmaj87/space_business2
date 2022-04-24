file(GLOB SRC_FILES    
    "components/*.cpp"
    "systems/*.cpp"
    "*.cpp"
)
target_sources(${PROJECT_NAME} 
    PRIVATE ${SRC_FILES})