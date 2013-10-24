FILE(GLOB SAMPLE_SOURCE *.cpp *.hpp)
FILE(GLOB SAMPLE_BIN *.obj *mtl *.tga)
add_sample("simple_model" "${SAMPLE_SOURCE}" "${SAMPLE_BIN}")
