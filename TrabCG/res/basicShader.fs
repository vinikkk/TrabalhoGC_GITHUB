#version 330
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform mat4 model;

uniform float ambientStrength;
uniform vec3 cameraPos;

//Directional Light
uniform vec3 directionalLightDir;
uniform float directionalLightIntesity;
uniform vec3 directionalLightPosition;

uniform Material material;
uniform Light light;

out vec4 color;

/*void main()
{
	vec3 fragNormal = normalize(light.position - fragPos);

	vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
	vec3 surfacePos = vec3(model * vec4(fragPos, 1));
	vec4 surfaceColor = texture(material.diffuse, texCoord);
	vec3 surfaceToLight = normalize(light.position - surfacePos);

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * 32;
	
	color = vec4(diffuse, 1.0);
}*/

void main()
{
	//Directional Light
	vec3 dirLight = normalize(directionalLightDir.xyz);

	//Ambient
	vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, texCoord));

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, texCoord));
	
	//Specular
	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
	vec3 specular = light.specular * spec * vec3(texture2D(material.specular, texCoord));
	
	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0) * texture2D(material.diffuse, texCoord);
	
	
	//gl_FragColor = texture2D(texture, texCoord0) * (lightColor * ambientStrength);
	//color = texture2D(texture, texCoord) * (clamp(dot(-lightPos, normal), 0.0, 1.0) + vec4(specular, 1.0));
	
	//color = vec4(ambient + diffuse + specular, 1.0) * texture2D(texture, texCoord);
}