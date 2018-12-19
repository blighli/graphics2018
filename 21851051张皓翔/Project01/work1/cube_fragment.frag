<<<<<<< HEAD
#version 460 core

in vec3 vertColor;
in vec2 textCoordination;
out vec4 FColor;
uniform sampler2D tex;

void main(){
	FColor = texture2D(tex, vec2(textCoordination.s, -textCoordination.t));

=======
#version 460 core

in vec3 vertColor;
in vec2 textCoordination;
out vec4 FColor;
uniform sampler2D tex;

void main(){
	FColor = texture2D(tex, vec2(textCoordination.s, -textCoordination.t));

>>>>>>> a8afaeee6689758db9e975ec51ec225f49416c7b
}