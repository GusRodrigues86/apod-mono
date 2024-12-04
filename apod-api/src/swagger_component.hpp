#ifndef api_SwaggerComponent_hpp
#define api_SwaggerComponent_hpp

#include "Constants.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

namespace APOD::API {
	class SwaggerComponent {
	public:

		/* The API description */
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)(Definitions::API_SERVICE_NAME, [] {
			oatpp::swagger::DocumentInfo::Builder builder;

			builder
				.setTitle("APOD API service")
				.setDescription("The public endpoints of the api")
				.setVersion("1.0")
				.setLicenseName("MIT")
				.setLicenseUrl("https://mit-license.org/")
				.addServer("http://localhost:8001", "local server on port 8001");

			return builder.build();
			}());

		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources) (Definitions::API_SERVICE_NAME, [] {

			return oatpp::swagger::Resources::streamResources(OATPP_SWAGGER_RES_PATH);
			}());
	};
}

#endif // !api_SwaggerComponent_hpp
