#ifndef MessageDTO_hpp
#define MessageDTO_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDTO : public oatpp::DTO {

	DTO_INIT(MessageDTO, DTO /* Extends */)

	DTO_FIELD(Int32, statusCode);   // Status code field
	DTO_FIELD(String, message);     // Message field

};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif /* MessageDTO_hpp */
