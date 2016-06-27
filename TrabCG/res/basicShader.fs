#version 330
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D texture;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec3 cameraPos;

uniform Material material;

out vec4 color;

void main()
{
	//Ambient
	vec3 ambient = lightColor * material.ambient;

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff * material.diffuse);
	
	//Specular
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * (spec * material.specular);
	
	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0) * texture2D(texture, texCoord);
	
	
	//gl_FragColor = texture2D(texture, texCoord0) * (lightColor * ambientStrength);
	//color = texture2D(texture, texCoord) * (clamp(dot(-lightPos, normal), 0.0, 1.0) + vec4(specular, 1.0));
	
	//color = vec4(ambient + diffuse + specular, 1.0) * texture2D(texture, texCoord);
}