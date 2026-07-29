namespace CollectableType {
	constexpr short Coin = 1;
	constexpr short Heart = 2;
	
}

class Collectable {
	public:
		short type;
		Vec2 position;
		bool collected = false;
		
		inline bool isCoin() const {
			return type == CollectableType::Coin;
		}
		inline bool isHeart() const {
			return type == CollectableType::Heart;
		}
	
	Collectable(const short inputType, const Vec2 inputPosition) : type(inputType), position(inputPosition) {}
};