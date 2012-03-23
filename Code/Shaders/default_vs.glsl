#version 420 core

layout(std140) uniform transform {		
	uniform	mat4 ModelViewMatrix;		
	uniform	mat4 ProjectionMatrix;		
} Transform;
uniform vec3 lightDir_vert;	
uniform vec3 cameraPos_vert;				

in  vec3 position_vert ; // Positions
in  vec3 color_vert;     // Colors : use per instance color or per vertex
in  vec3 normal_vert ;   // Normals
in  vec3 inst_pos;       // Attrib pour les instances - Translate
in  vec3 inst_scl;       // Attrib pour les instances - Scale
in  mat3 inst_rot;       // Attrib pour les instances - Rotate

out vec3 position_frag ; 
out vec3 color_frag;     
out vec3 normal_frag;    

out vec3 eyeVec_frag;    
out vec3 lightDir_frag;  

void main()
{
	// Matrice de transformation
	mat4 MVP      = Transform.ProjectionMatrix * Transform.ModelViewMatrix ;
	// Position des vertex
	position_frag = position_vert*inst_scl*inst_rot+inst_pos;
	gl_Position   = MVP*(vec4(position_frag,1.0));                // La position n'est pas la meme en fonction de l'instance
	vec4 vVertex  = Transform.ModelViewMatrix * vec4(position_frag,1.0);
	
	color_frag    = color_vert;
	normal_frag   = normalize(normal_vert*inst_rot);
	
	eyeVec_frag   = normalize(vVertex.xyz-cameraPos_vert);
	lightDir_frag = normalize(lightDir_vert);
}