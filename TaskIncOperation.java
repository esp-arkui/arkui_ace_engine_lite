package com.huawei.operation;

import com.huawei.entity.pojo.CodeCheckTaskIncVo;
import com.huawei.enums.CodeCheckCollectionName;
import com.huawei.enums.SyncStatus;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.data.mongodb.core.query.Update;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * @Description 增量任务表 关联增量检查的数据表
 * @ClassName com.huawei.operation
 * @since 2022/11/8  09:40
 **/
@Component
public class TaskIncOperation {
    @Autowired
    @Qualifier("codeCheckMongoTemplate")
    private MongoTemplate mongoTemplate;

    /**
     * 通过uuid和mrUrl查询数据
     *
     * @param uuid  uuid
     * @param mrUrl mergeRequest url
     * @return List<CodeCheckTaskIncVo> {@linkplain CodeCheckTaskIncVo}
     * @since 2022/11/8
     */
    public List<CodeCheckTaskIncVo> getByUuidAndMrUrl(String uuid, String mrUrl) {
        Criteria criteria = Criteria.where("uuid").is(uuid).and("mrUrl").is(mrUrl);
        return mongoTemplate.find(Query.query(criteria), CodeCheckTaskIncVo.class, CodeCheckCollectionName.TASK_INC);
    }

    /**
     * 通过uuid和mrUrl删除数据
     *
     * @param taskIncVo CodeCheckTaskIncVo 实体
     * @return List<CodeCheckTaskIncVo> {@linkplain CodeCheckTaskIncVo}
     * @since 2022/11/8
     */
    public void remove(CodeCheckTaskIncVo taskIncVo) {
        Criteria criteria = Criteria.where("uuid").is(taskIncVo.getUuid()).and("mrUrl").is(taskIncVo.getMrUrl());
        mongoTemplate.remove(Query.query(criteria), CodeCheckCollectionName.TASK_INC);
    }

    /**
     * 将增量任务详情入库
     *
     * @param taskIncVo CodeCheckTaskIncVo 实体
     * @return List<CodeCheckTaskIncVo> {@linkplain CodeCheckTaskIncVo}
     * @since 2022/11/8
     */
    public void insert(CodeCheckTaskIncVo taskIncVo) {
        mongoTemplate.insert(taskIncVo);
    }

    /**
     * 将增量任务详情入库
     *
     * @param taskId 增量任务taskid
     * @return List<CodeCheckTaskIncVo> {@linkplain CodeCheckTaskIncVo}
     * @since 2022/11/8
     */
    public List<CodeCheckTaskIncVo> getTaskByTaskId(String taskId) {
        return mongoTemplate.find(Query.query(Criteria.where("taskId").is(taskId)),
                CodeCheckTaskIncVo.class);
    }

    /**
     * getTaskByStatus
     *
     * @param status status
     * @return List<CodeCheckTaskIncVo>
     */
    public List<CodeCheckTaskIncVo> getTaskByStatus(List<Integer> status) {
        Query query = Query.query(Criteria.where("processing").in(status));
        return mongoTemplate.find(query, CodeCheckTaskIncVo.class, CodeCheckCollectionName.TASK_INC);
    }

    /**
     * updateProcessById
     *
     * @param id     id
     * @param status status
     */
    public void updateProcessById(String id, int status) {
        Query query = Query.query(Criteria.where("id").is(id));
        Update update = Update.update("processing", status);
        mongoTemplate.updateFirst(query,update,CodeCheckTaskIncVo.class);
    }

    /**
     * 同步出错后就不能再修改为成功
     *
     * @param id 主键Id
     * @return boolean
     */
    public boolean updateSuccess(String id){
        Criteria criteria = Criteria.where("id").is(id).and("processing").ne(SyncStatus.SYNC_FAILED);
        Update update = Update.update("processing", SyncStatus.SYNC_SUCCESS);
        return mongoTemplate.updateFirst(Query.query(criteria), update, CodeCheckTaskIncVo.class).wasAcknowledged();
    }

    /**
     * 根据uuid和taskId查询task
     *
     * @param taskId 任务id
     * @param uuid 门禁uuid
     * @return 响应信息
     */
    public CodeCheckTaskIncVo getTaskByUuidAndTaskId(String taskId, String uuid){
        Criteria criteria = Criteria.where("uuid").is(uuid).and("taskId").is(taskId);
        return mongoTemplate.findOne(Query.query(criteria), CodeCheckTaskIncVo.class, CodeCheckCollectionName.TASK_INC);
    }

    public List<CodeCheckTaskIncVo> getTaskByUuid(String uuid) {
        Criteria criteria = Criteria.where("uuid").is(uuid);
        return mongoTemplate.find(Query.query(criteria), CodeCheckTaskIncVo.class, CodeCheckCollectionName.TASK_INC);
    }
}
