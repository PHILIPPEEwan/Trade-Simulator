#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME_LEN 128
#define MAX_CODE_LEN 16
#define MAX_COUNTRIES 200
#define MAX_PRODUCTS 500
#define MAX_BARRIERS 50

// Economic constants
#define DEFAULT_ELASTICITY -1.5
#define WELFARE_PRECISION 0.001
#define MAX_SIMULATION_YEARS 10

// Trade barrier types
typedef enum {
    BARRIER_TARIFF_FIXED,
    BARRIER_TARIFF_PROGRESSIVE,
    BARRIER_QUOTA_ABSOLUTE,
    BARRIER_QUOTA_TARIFF_RATE,
    BARRIER_SUBSIDY,
    BARRIER_EMBARGO,
    BARRIER_ADMIN_DELAY,
    BARRIER_CURRENCY_CONTROL
} BarrierType;

// Country structure
typedef struct Country {
    char code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    double gdp;
    double population;
    double exchange_rate;
    struct Country* next;
} Country;

// Product structure
typedef struct Product {
    char hs_code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    char category[MAX_NAME_LEN];
    double base_price;
    double elasticity;
    struct Product* next;
} Product;

// Trade flow structure
typedef struct TradeFlow {
    Country* exporter;
    Country* importer;
    Product* product;
    double volume;
    double value;
    int year;
    struct TradeFlow* next;
} TradeFlow;

// Trade barrier structure
typedef struct TradeBarrier {
    BarrierType type;
    double rate;  // Tariff rate or quota amount
    double secondary_rate;  // For progressive tariffs
    double threshold;  // For quotas or progressive tariffs
    Country* source_country;
    Country* target_country;
    Product* product;
    bool is_active;
    struct TradeBarrier* next;
} TradeBarrier;

// Economic impact structure
typedef struct EconomicImpact {
    double trade_volume_change;
    double price_change_consumer;
    double price_change_producer;
    double government_revenue;
    double consumer_surplus_change;
    double producer_surplus_change;
    double deadweight_loss;
    double employment_change;
    double gdp_impact;
} EconomicImpact;

// Simulation scenario
typedef struct Scenario {
    char name[MAX_NAME_LEN];
    TradeBarrier* barriers;
    EconomicImpact* impacts;
    double timestamp;
    struct Scenario* next;
} Scenario;

// Simulation parameters
typedef struct SimulationParams {
    int time_horizon_years;
    bool enable_retaliation;
    bool enable_supply_chain_effects;
    double retaliation_threshold;
    double currency_volatility;
} SimulationParams;

// Lowercase aliases for compatibility
typedef Country country_t;
typedef Product product_t;
typedef TradeFlow trade_flow_t;
typedef TradeBarrier trade_barrier_t;
typedef EconomicImpact economic_impact_t;
typedef Scenario scenario_t;
typedef SimulationParams simulation_params_t;
typedef BarrierType barrier_type_t;

#endif // TYPES_H