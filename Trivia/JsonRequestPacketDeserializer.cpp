#include "JsonRequestPacketDeserializer.h"

std::vector<std::uint8_t> JsonRequestPacketDeserializer::serializeResponse(ErrorResponse err)
{
    nlohmann::json j = err;
    return nlohmann::json::parse(j);
}

std::vector<std::uint8_t> JsonRequestPacketDeserializer::serializeResponse(LoginResponse l)
{
    nlohmann::json j = l;
    return nlohmann::json::parse(j);
}

std::vector<std::uint8_t> JsonRequestPacketDeserializer::serializeResponse(SignupResponse s)
{
    nlohmann::json j = s;
    return nlohmann::json::parse(j);
}
