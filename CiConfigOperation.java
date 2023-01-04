package com.huawei.operation;

import com.huawei.ci.common.entity.cicd.CiProjectQuery;
import com.huawei.ci.common.entity.cicd.CiProjectVo;
import com.huawei.enums.CiCollectionName;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class CiConfigOperation {
    @Autowired
    @Qualifier("ciMongoTemplate")
    private MongoTemplate mongoTemplate;
    /**
     * 查询没有流水线信息的ci项目信息
     *
     * @param ciProjectQuery 查询条件
     * @return ci项目信息
     */
    public List<CiProjectVo> getVoWithOutPipeline(CiProjectQuery ciProjectQuery) {
        Criteria criteria = Criteria.where("nameSpace").is(ciProjectQuery.getNameSpace());
        if (StringUtils.isNotBlank(ciProjectQuery.getManifestBranch())) {
            criteria.and("manifestBranch").is(ciProjectQuery.getManifestBranch());
        }
        Query query = Query.query(criteria);
        query.fields().exclude("dailyPipelineList");
        return mongoTemplate.find(query, CiProjectVo.class, CiCollectionName.CI_CONFIG);
    }
}
