#version 420 core

layout(std140) uniform material {
	uniform	vec4 ambient;				
	uniform	vec4 diffuse;				
	uniform	vec4 specular;				
	float shininess;					
} Material;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;

in vec3 position_frag;
in vec3 color_frag; 
in vec3 normal_frag;
in vec3 lightDir_frag;
in vec3 eyeVec_frag;

out vec4 frag_color;

subroutine vec4 shadeModelType( vec3 color, vec3 normal);
subroutine uniform shadeModelType shadeModel;

subroutine( shadeModelType )
vec4 phongModel( vec3 col, vec3 norm )
{
  // Default : Ambient color
  vec3 final_color = Material.ambient.xyz;
  
  float lambertTerm = dot(norm,lightDir_frag);
  if (lambertTerm > 0.0)
  {
    // Diffuse color
	final_color +=  Material.diffuse.xyz * vec3(lambertTerm,lambertTerm,lambertTerm);
	// Specular color
	vec3 R = reflect(-lightDir_frag, norm);
	float specular = pow(max(dot(R, eyeVec_frag), 0.0), Material.shininess);
	final_color +=  Material.specular.xyz * vec3(specular,specular,specular);
  }
  return vec4(final_color,1.0);
}

subroutine( shadeModelType )
vec4 phongVertexColorModel( vec3 col, vec3 norm )
{
  // Default : Ambient color
  vec3 final_color = col;
  
  float lambertTerm = dot(norm,lightDir_frag);
  if (lambertTerm > 0.0)
  {
    // Diffuse color
	final_color +=  Material.diffuse.xyz * vec3(lambertTerm,lambertTerm,lambertTerm);
	// Specular color
	vec3 R = reflect(-lightDir_frag, norm);
	float specular = pow(max(dot(R, eyeVec_frag), 0.0), Material.shininess);
	final_color +=  Material.specular.xyz * vec3(specular,specular,specular);
  }
  return vec4(final_color,1.0);
}

subroutine( shadeModelType )
vec4 goochModel( vec3 col, vec3 norm )
{	
	vec3 warm_color = vec3(1.0,0.6,0.2);
	vec3 cool_color = vec3(0.0,0.4,0.8);
	vec4 final_color;

	final_color = vec4(((1 + dot(norm, lightDir_frag)) / 2 * warm_color) + ((1 - dot(norm, lightDir_frag)) / 2 * cool_color), 1.0);
 
	return final_color;
}

subroutine( shadeModelType )
vec4 toonModel( vec3 col, vec3 norm )
{
	float intensity;
	vec4 final_color;
	
	intensity  = dot(lightDir_frag , norm);
	if (intensity > 0.95)      final_color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5 ) final_color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25) final_color = vec4(0.4,0.2,0.2,1.0);
	else                       final_color = vec4(0.2,0.1,0.1,1.0);
	return final_color;
}

subroutine( shadeModelType )
vec4 normalColorModel( vec3 col, vec3 norm )
{
	
	return vec4((vec3(1.0,1.0,1.0)+norm)/2.,1.0);
}

subroutine( shadeModelType )
vec4 classiqueModel( vec3 col, vec3 norm )
{
	return vec4(col*abs(dot(norm,vec3(0.9,0.5,0.3))),1.0);
}

subroutine( shadeModelType )
vec4 gridModel( vec3 col, vec3 norm )
{
	float steps=0.6;
	vec3 colorLine = vec3(0.2,0.1,0.1);
	vec3 final_color;
	vec3 pos=vec3(abs(position_frag.x),abs(position_frag.y),abs(position_frag.z));
	
	if ((pos.x-float(int(pos.x/steps))*steps)<0.01) final_color = colorLine;
	else{
		if ((pos.y-float(int(pos.y/steps))*steps)<0.01) final_color = colorLine;
		else{
			if ((pos.z-float(int(pos.z/steps))*steps)<0.01) final_color = colorLine;
			else{
				final_color = Material.ambient.xyz;
		  
				float lambertTerm = dot(norm,lightDir_frag);
				if (lambertTerm > 0.0)
				{
					// Diffuse color
					final_color +=  Material.diffuse.xyz * vec3(lambertTerm,lambertTerm,lambertTerm);
					// Specular color
					vec3 R = reflect(-lightDir_frag, norm);
					float specular = pow(max(dot(R, eyeVec_frag), 0.0), Material.shininess);
					final_color +=  Material.specular.xyz * vec3(specular,specular,specular);
				}
			}
		}
	}
	return vec4(final_color,1.0);
}

subroutine( shadeModelType )
vec4 ignModel( vec3 col, vec3 norm )
{

	float z=position_frag.z;
	vec4 color_=vec4(col,1.0);
	vec4 final_color;

	const float maxHeight = 200;
	const float offset = 88.0;
	const int nbStep = 3;
	const float rangeFullColored = 0.01;
	const float rangeGradientColored = 0.01;
	
	//how much will be multiplied the color in ambient area
	const float coefBackLighting = 0.15;
	const float coefMultAmbient = 0.4; //0.53

	const vec4 colorLine    = vec4(205.0 / 255.0, 195.0 / 255.0, 195.0 / 255.0, 1.0);
	const vec4 colorNeutral = vec4(235.0 / 255.0, 235.0 / 255.0, 235.0 / 255.0, 1.0);
	const vec4 colorForest  = vec4(135.0 / 255.0, 165.0 / 255.0, 125.0 / 255.0, 1.0);

	// Get a float between 0.0 and 1.0 (0.0 = bottom of a 'slice', 1.0 = top)
	float heightRange = maxHeight - offset;
	
	float height = z;
	height = height - offset;
	
	height = height / heightRange;
	height = height * nbStep;
	height = fract(height);
	
	// Defining colors according to the position in 0.0 to 1.0
	float beginTr  = - height + rangeGradientColored;
	beginTr = clamp (beginTr, 0.0, rangeGradientColored);
	beginTr = beginTr / rangeGradientColored;

	float endTr = height - (1.0 - rangeGradientColored - rangeFullColored);
	endTr = clamp (endTr, 0.0, rangeGradientColored);
	endTr = endTr / rangeGradientColored;

	float ratioColorLine = max(beginTr, endTr);
	float ratioColorNeutral = 1.0 - ratioColorLine;

	// Diffuse color
	vec4 usedNeutralColor = (color_.b * colorForest) + ((1 - color_.b) * colorNeutral);
	vec4 colorDiffuse = (ratioColorLine * colorLine) + (ratioColorNeutral * usedNeutralColor);
	float dotLight = dot(norm, lightDir_frag);
	
	// Slight back-lighting
	float mult;
	if (dotLight < 0.0) mult = coefBackLighting;
	else mult = 1.0;
	
	dotLight = abs(dotLight * mult);
	dotLight = clamp (dotLight, 0.0, 1.0);
	dotLight = abs(dotLight*0.90);

	//multAmbient goes from coefMultAmbient to 1.0
	float multAmbient = ((1.0 - coefMultAmbient) * dotLight) + coefMultAmbient;

	final_color = multAmbient * colorDiffuse;
	final_color.a = 1.0;
	
	return final_color;
}

subroutine( shadeModelType )
vec4 terrain3DModel( vec3 col, vec3 norm )
{
	vec3 worldNormal = normalize(norm);
	float Stretching = 0.3;
	float ambient    = 0.2;
	
	// Generate planes blending coeffs
	vec3 absNormal   = abs(worldNormal);
	vec3 blendnormal = normalize(pow(absNormal, vec3(8.0)));
	float blendSqrX  = blendnormal.x * blendnormal.x;
	float blendSqrY  = blendnormal.y * blendnormal.y;
	float blendSqrZ  = blendnormal.z * blendnormal.z;
	
	// Generate planes uvs
	vec2 texCoordX = vec2(-position_frag.z, -position_frag.y);
	vec2 texCoordY = vec2(-position_frag.x, -position_frag.z);
	vec2 texCoordZ = vec2( position_frag.x, -position_frag.y);
	
	// Sample color maps
	vec4 color1 = vec4(0.0);
	color1 += texture2D(tex1, texCoordX.xy * Stretching) * blendSqrX;
	color1 += texture2D(tex1, texCoordY.xy * Stretching) * blendSqrY;
	color1 += texture2D(tex1, texCoordZ.xy * Stretching) * blendSqrZ;
	
	vec4 color2 = vec4(0.0);
	color2 += texture2D(tex2, texCoordX.xy * Stretching) * blendSqrX;
	color2 += texture2D(tex2, texCoordY.xy * Stretching) * blendSqrY;
	color2 += texture2D(tex2, texCoordZ.xy * Stretching) * blendSqrZ;
	
	vec4 color3 = vec4(0.0);
	color3 += texture2D(tex3, texCoordX.xy * Stretching) * blendSqrX;
	color3 += texture2D(tex3, texCoordY.xy * Stretching) * blendSqrY;
	color3 += texture2D(tex3, texCoordZ.xy * Stretching) * blendSqrZ;
	
	vec4 color4 = vec4(0.0);
	color4 += texture2D(tex4, texCoordX.xy * Stretching) * blendSqrX;
	color4 += texture2D(tex4, texCoordY.xy * Stretching) * blendSqrY;
	color4 += texture2D(tex4, texCoordZ.xy * Stretching) * blendSqrZ;
	
	vec4 mixcolor = vec4(0.0);
	mixcolor = mix(color1  , color2, col.x);
	mixcolor = mix(mixcolor, color3, col.y);
	mixcolor = mix(mixcolor, color4, col.z);		
			
	// Do the lighting (diffuse + ambient)
	float diffuseFactor = clamp(dot(worldNormal, lightDir_frag),0.,1.);

	// Calculating and return the Final Color
	vec4 final_color = (diffuseFactor+ambient)*mixcolor;
	final_color.a = 1.0;
	return final_color;	//vec4(worldNormal,0.0);
}


void main()
{
	frag_color = shadeModel( color_frag, normal_frag );
}
