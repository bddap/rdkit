#include <catch2/catch_all.hpp>

#include <GraphMol/SmilesParse/SmilesParse.h>
#include <GraphMol/SmilesParse/SmilesWrite.h>

using namespace RDKit;

TEST_CASE("SMILES conversion", "[benchmark][smiles]") {
  auto smiles =
      "Nc1nc(N)c(-c2ccc(CNc3ccc([N+](=O)[O-])cc3)cc2)c(COCc2ccccc2)n1";
  std::unique_ptr<ROMol> mol{SmilesToMol(smiles)};

  BENCHMARK("SmilesToMol") {
    std::unique_ptr<ROMol> mol{SmilesToMol(smiles)};
    REQUIRE(mol);
  };

  BENCHMARK("MolToSmiles") {
    auto after_round_trip = MolToSmiles(*mol);
    REQUIRE(after_round_trip == smiles);
  };
}
